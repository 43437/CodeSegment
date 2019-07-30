#include "CTestTable1.h"
#include "persistDataDef.h"


CTestTable1::CTestTable1(MYSQL* conn)
	:CPersistObj(conn)
{
	m_strTableName = "test_table2";
	m_nField = 4;
}


CTestTable1::~CTestTable1()
{
}

int CTestTable1::reflect(vector<string> vecField)
{
	int nRet = persist::PERSIST_RET_FAILED;

	if (vecField.size() == m_nField)
	{
		this->m_nID = atoi(vecField[0].c_str());
		this->m_strName = vecField[1];
		this->m_strBirth = vecField[2];
		this->m_strInfo = vecField[3];

		nRet = persist::PERSIST_RET_SUCCESS;
	}
	else
	{
		nRet = persist::PERSIST_RET_FAILED;			//reflect failed.
	}

	return nRet;
}

std::string CTestTable1::SQLInsert()		//transfor member to database field
{
	std::string strSQL("insert into ");
	strSQL += m_strTableName + " (name, birth, info) values ( "+QUOTE(this->m_strName)+","+QUOTE(this->m_strBirth)+","+QUOTE(this->m_strInfo)+" )";
	
	return strSQL;
}

void CTestTable1::setName(string strName)
{
	this->m_strName = strName;
	m_mapUpdateField["name"] = strName;
}
void CTestTable1::setBirth(string strBirth)
{
	this->m_strBirth = strBirth;
	m_mapUpdateField["birth"] = strBirth;
}

void CTestTable1::setInfo(string strInfo)
{
	this->m_strInfo = strInfo;
	m_mapUpdateField["info"] = strInfo;
}