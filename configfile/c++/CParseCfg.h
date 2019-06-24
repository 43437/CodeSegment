#ifndef _PARSE_2019052820_
#define _PARSE_2019052820_

#include <iostream>
#include <map>

class CParseCfg
{
public:
	CParseCfg(const std::string& strCfgFile);
	CParseCfg();
	~CParseCfg();
	void setCfgFile(const std::string& strCfgFile);

	bool ParseCfg(std::map<std::string, std::string>& mapCfgPairs);
	bool ParseCfgFile(const std::string& strCfgFile, std::map<std::string, std::string>& mapCfgPairs, const std::string& strDelimiter = "=");
	bool WriteCfgFile(const std::string& strCfgFile, const std::map<std::string, std::string>& mapCfgPairs, const std::string& strDelimiter = "=");
private:
	std::string m_strCfgFile;
};

#endif