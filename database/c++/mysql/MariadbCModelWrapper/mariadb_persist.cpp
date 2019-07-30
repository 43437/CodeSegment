#include "mariadb_persist.h"
#include "stdio.h"
#include <map>
#include <string>
#include <vector>

using std::vector;
using std::string;

int mdb_begin_session(MYSQL** mdb_conn)
{
	const char* szServer = "localhost";			//server location
	const char* szUser = "root";				//user name
	const char* szPassword = "xxxxx";		//password
	const char* szDatabase = "test";			//database

	*mdb_conn = mysql_init(NULL);

	if (*mdb_conn == NULL)
	{
		return MDB_ERR_INIT;					//init failed.
	}
	else
	{
		;										//goes very well, go on
	}

	if (mysql_real_connect(*mdb_conn, szServer, szUser, szPassword,
		szDatabase, 0, NULL, 0) == NULL)
	{
		mysql_close(*mdb_conn);
		return MDB_ERR_CONN;					//connect failed.
	}
	else
	{
		return MDB_RET_SUCCESS;					//connect success.
	}
}

void mdb_end_session(MYSQL* mdb_conn)
{
	mysql_close(mdb_conn);
}
//
//int mdb_sql_get(MYSQL* mdb_conn, const char* szSQL, char** pszResult)
//{
//	MYSQL_ROW row;
//	MYSQL_RES* res;
//
//	if (mysql_query(mdb_conn, szSQL)) {
//		//fprintf(stderr, "%s\n", mysql_error(mdb_conn));
//		return MDB_ERR_GET;					//query failed.
//	}
//
//	res = mysql_use_result(mdb_conn);
//
//	unsigned int num_fields;
//	unsigned int i;
//
//	num_fields = mysql_num_fields(res);
//	while ((row = mysql_fetch_row(res)))
//	{
//		unsigned long* lengths;
//		lengths = mysql_fetch_lengths(res);
//		for (i = 0; i < num_fields; i++)
//		{
//			printf("%.*s ", (int)lengths[i], row[i] ? row[i] : "NULL");
//		}
//		printf("\n");
//	}
//
//	mysql_free_result(res);
//
//	return MDB_RET_SUCCESS;
//}

int mdb_sql_excute(MYSQL* mdb_conn, const char* szSQL)
{
	if (mysql_query(mdb_conn, szSQL)) {
		return MDB_RET_FAILED;					//query failed.
	}

	return MDB_RET_SUCCESS;
}

int mdb_get_lastid(MYSQL* mdb_conn)
{
	int nRet = INVALID_UID;
	MYSQL_ROW row;
	MYSQL_RES* res;
	const char* szSQL = "select last_insert_id();";

	if (mysql_query(mdb_conn, szSQL)) {
		fprintf(stderr, "%s\n", mysql_error(mdb_conn));
		return MDB_ERR_GET;					//query failed.
	}

	if (res = mysql_use_result(mdb_conn))
	{
		if (row = mysql_fetch_row(res))
		{
			nRet = atoi(row[0]);
		}
	}

	mysql_free_result(res);

	return nRet;
}

int mdb_load(MYSQL* mdb_conn, const string& strTableName, vector<vector<string>>& vecValue)
{
	vecValue.clear();
	string strSQL("select * from ");
	strSQL += strTableName;
	return mdb_query(mdb_conn, strSQL, vecValue);
}

int mdb_query(MYSQL* mdb_conn, const string& strSQL, vector<vector<string>>& vecValue)
{
	int nRet = MDB_RET_SUCCESS;
	vecValue.clear();
	MYSQL_ROW row;
	MYSQL_RES* res;

	if (mysql_query(mdb_conn, strSQL.c_str())) {
		return MDB_ERR_GET;					//query failed.
	}

	string strField("");
	vector<string> vecRow;
	if (NULL != (res = mysql_use_result(mdb_conn)))
	{
		unsigned int num_fields;
		unsigned int i;
		unsigned long* lengths;

		num_fields = mysql_num_fields(res);
		while ((row = mysql_fetch_row(res)))
		{
			vecRow.clear();
			lengths = mysql_fetch_lengths(res);
			for (i = 0; i < num_fields; i++)
			{
				if (NULL != row[i])
				{
					strField.assign(row[i], (int)lengths[i]);
					vecRow.push_back(strField);						//save column
				}
			}
			vecValue.push_back(vecRow);								//save row
		}
	}
	else
	{
		nRet = MDB_RET_FAILED;
	}

	mysql_free_result(res);

	return nRet;
}