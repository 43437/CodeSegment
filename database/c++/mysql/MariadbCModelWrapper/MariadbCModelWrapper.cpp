// MariadbCModelWrapper.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <mysql.h>
#include "mariadb_persist.h"
#include "CTestTable1.h"
#include <vector>
#include <string>
#include <map>
#include "persistDataDef.h"

using std::vector;
using std::string;
using std::map;

int main()
{
    std::cout << "Hello World!\n"; 

	MYSQL* conn;
	mdb_begin_session(&conn);

	vector<vector<string>> vecRecord;
	map<int, CTestTable1> mapObjTestTable2;

	if (MDB_RET_SUCCESS == mdb_load(conn, "test_table2", vecRecord))
	{
		CTestTable1 ct1(conn);
		for (vector<vector<string>>::const_iterator itRecord=vecRecord.begin(); vecRecord.end()!=itRecord; ++itRecord)
		{
			if (persist::PERSIST_RET_SUCCESS == ct1.reflect(*itRecord))
			{
				mapObjTestTable2.insert(std::make_pair(ct1.getID(), ct1));
			}
			else
			{
				printf("reflect failed.\n");
			}
		}
	}

	size_t nObjSize = mapObjTestTable2.size();
	printf("record size: %d\n", (int)nObjSize);

	for (map<int, CTestTable1>::const_iterator itObj=mapObjTestTable2.begin(); mapObjTestTable2.end()!=itObj; ++itObj)
	{
		const CTestTable1& obj = itObj->second;
		printf("id: %d\nname: %s\nbirth; %s\ninfo: %s\n\n", obj.getID(), obj.getName().c_str(), obj.getBirth().c_str(), obj.getInfo().c_str());
	}

	//delete id=9
	map<int, CTestTable1>::iterator itObj = mapObjTestTable2.find(9);
	if (mapObjTestTable2.end() != itObj)
	{
		CTestTable1 obj9 = itObj->second;
		if (persist::PERSIST_RET_SUCCESS == obj9.DoDelete())
		{
			printf("delete id=9 record success.\n");
		}
		else
		{
			printf("delete id=9 record failed.\n");
		}
	}
	else
	{
		;
	}

	//update id=10
	itObj = mapObjTestTable2.find(10);
	if (mapObjTestTable2.end() != itObj)
	{
		CTestTable1& obj10 = itObj->second;
		obj10.setInfo("update by me.");
		if (persist::PERSIST_RET_SUCCESS == obj10.DoUpdate())
		{
			printf("update id=10 record success.\n");
		}
		else
		{
			printf("update id=10 record failed.\n");
		}
	}
	else
	{
		;
	}

	mdb_end_session(conn);

	exit(0);
}