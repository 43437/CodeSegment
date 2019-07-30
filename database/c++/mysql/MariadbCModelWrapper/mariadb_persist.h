#ifndef __MARIADB_PERSIST_20190727__
#define __MARIADB_PERSIST_20190727__

#include "stdlib.h"
#include "mysql.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

enum
{
	MDB_RET_FAILED=-1,			//failed
	MDB_RET_SUCCESS,		//success
	MDB_ERR_INIT,			//init failed
	MDB_ERR_CONN,			//connect failed
	MDB_ERR_GET,			//get failed
	MDB_ERR_PARAM,			//param format error
};

enum
{
	MDB_ERR_INSERT_AGAIN=-1000,	//repeat insert
};

enum
{
	INVALID_UID,
};

int mdb_begin_session(MYSQL** mdb_conn);
void mdb_end_session(MYSQL* mdb_conn);
int mdb_sql_excute(MYSQL* mdb_conn, const char* szSQL);
int mdb_get_lastid(MYSQL* mdb_conn);
int mdb_load(MYSQL* mdb_conn, const string& strTableName, vector<vector<string>>& vecValue);
int mdb_query(MYSQL* mdb_conn, const string& strSQL, vector<vector<string>>& vecValue);

#endif