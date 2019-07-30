#include "CPersistObj.h"
#include "persistDataDef.h"
#include "mariadb_persist.h"

using persist::PERSIST_RET_FAILED;
using persist::PERSIST_RET_SUCCESS;

CPersistObj::CPersistObj(MYSQL* conn)
	: m_nID(INVALID_UID)
	, m_nField(0)
	, mdb_conn(conn)
	, LQ("\"")
	, RQ("\"")
{
}


CPersistObj::~CPersistObj()
{
}

int CPersistObj::DoInsert()
{
	int nRet = INVALID_UID;

	if ( INVALID_UID == this->m_nID )		//only insert one which id is invalid, avoid repeat insert
	{
		std::string strSQL = SQLInsert();
		// excute sql
		if (PERSIST_RET_FAILED != (nRet = SQLExcute(strSQL)))
		{
			if (INVALID_UID != (nRet = mdb_get_lastid(mdb_conn)))
			{
				this->m_nID = nRet;
			}
			else
			{
				this->m_nID = INVALID_UID;
			}
		}
		else
		{
			this->m_nID = INVALID_UID;
		}

		return this->m_nID;
	}
	else
	{
		return MDB_ERR_INSERT_AGAIN;
	}
}

int CPersistObj::DoUpdate()
{
	std::string strSQL = SQLUpdate();
	// excute sql
	return SQLExcute(strSQL);
}

int CPersistObj::DoDelete()
{
	if (INVALID_UID != this->m_nID)
	{
		std::string strSQL = SQLDelete();
		// excute sql
		return SQLExcute(strSQL);
	}
	else
	{
		return PERSIST_RET_FAILED;
	}
}

int CPersistObj::SQLExcute(std::string strSQL)
{
	return (MDB_RET_SUCCESS == mdb_sql_excute(this->mdb_conn, strSQL.c_str())) ? PERSIST_RET_SUCCESS : PERSIST_RET_FAILED;
}

std::string CPersistObj::SQLDelete()
{
	std::string strSQL("delete from ");
	strSQL += m_strTableName + " where id= " + std::to_string(this->m_nID);

	return strSQL;
}

std::string CPersistObj::SQLUpdate()
{
	std::string strSQL("");

	if (!m_mapUpdateField.empty())
	{
		strSQL = strSQL + "update " + m_strTableName + " set ";

		for (std::map<std::string, std::string>::const_iterator itField = m_mapUpdateField.begin(); m_mapUpdateField.end() != itField; ++itField)
		{
			const std::string& strKey = itField->first;
			const std::string& strValue = itField->second;
			strSQL = strSQL + " " + strKey + "=" + LQ + strValue + RQ + ",";
		}
		strSQL.pop_back();
		strSQL = strSQL + " where id=" + std::to_string(this->m_nID);

		m_mapUpdateField.clear();
	}
	else
	{
		;	//no changed
	}

	return strSQL;
}