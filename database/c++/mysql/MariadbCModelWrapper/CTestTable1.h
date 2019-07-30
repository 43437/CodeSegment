#ifndef __CTestTable1_20190727_H__
#define __CTestTable1_20190727_H__

#include "CPersistObj.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class CTestTable1 :public CPersistObj
{
public:
	CTestTable1(MYSQL* conn);
	~CTestTable1();
	virtual std::string SQLInsert();

	int reflect(vector<string> vecField);

	void setName(string strName);
	void setBirth(string strBirth);
	void setInfo(string strInfo);

	int getID() const { return this->m_nID; };
	std::string getName() const { return this->m_strName; };
	std::string getBirth() const { return this->m_strBirth; };
	std::string getInfo() const { return this->m_strInfo; };

private:
	std::string m_strName;
	std::string m_strBirth;
	std::string m_strInfo;
};

#endif