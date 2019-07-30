#ifndef __PERSISTOBJ_201907272225_H__
#define __PERSISTOBJ_201907272225_H__

#include <string>
#include <map>
#include <vector>
#include "mariadb_persist.h"

using std::string;
using std::vector;
using std::map;

class CPersistObj
{
public:
	CPersistObj(MYSQL* conn);
	~CPersistObj();
	virtual int reflect(vector<string> vecField) = 0;		//reflect info from database query result
	virtual std::string SQLInsert()=0;					//transfor member to database field
	virtual std::string SQLUpdate();					//transfor member to database field
	virtual std::string SQLDelete();					//transfor member to database field
	virtual int DoUpdate();
	virtual int DoDelete();
	virtual int DoInsert();
	int SQLExcute(std::string strSQL);

protected:
	const std::string LQ;
	const std::string RQ;

protected:
	int m_nID;
	std::string m_strTableName;			//table name
	MYSQL* mdb_conn;					//database connection

	std::map<std::string, std::string> m_mapUpdateField;
	int m_nField;
};

#endif