#include "CParseCfg.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>


CParseCfg::CParseCfg():
	m_strCfgFile("")
{
}

CParseCfg::CParseCfg(const std::string& strCfgFile):
	m_strCfgFile(strCfgFile)
{

}

void CParseCfg::setCfgFile(const std::string& strCfgFile)
{
	this->m_strCfgFile = strCfgFile;
}

bool CParseCfg::ParseCfg(std::map<std::string, std::string>& mapCfgPairs)
{
	mapCfgPairs.clear();
	return ParseCfgFile(m_strCfgFile, mapCfgPairs);
}

bool CParseCfg::ParseCfgFile(const std::string& strCfgFile, std::map<std::string, std::string>& mapCfgPairs, const std::string& strDelimiter/* = "="*/)
{
	bool bRet = false;

	mapCfgPairs.clear();
	std::ifstream cFile(strCfgFile);

	if (cFile.is_open())
	{
		std::string line;
		while (getline(cFile, line)) 
		{
			line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
			if (line[0] == '#' || line.empty())
				continue;
			size_t delimiterPos = line.find(strDelimiter);
			std::string name = line.substr(0, delimiterPos);
			std::string value = line.substr(delimiterPos + 1);
			mapCfgPairs.insert(std::make_pair(name, value));

			line.clear();
		}

		if (!mapCfgPairs.empty())
		{
			bRet = true;
		}
		else
		{
			bRet = false;
		}
	}
	else 
	{
		bRet = false;		//open file failed.
	}

	return bRet;
}

bool CParseCfg::WriteCfgFile(const std::string& strCfgFile, const std::map<std::string, std::string>& mapCfgPairs, const std::string& strDelimiter/* = "="*/)
{
	bool bRet = true;
	std::ofstream cFile(strCfgFile);
	std::string key = "";
	std::string value = "";
	std::string lineVal = "";
	if (cFile.is_open())
	{
		for (std::map<std::string, std::string>::const_iterator itCfgPair = mapCfgPairs.cbegin(); mapCfgPairs.cend() != itCfgPair; ++itCfgPair)
		{
			key = itCfgPair->first;
			value = itCfgPair->second;
			lineVal = key + strDelimiter + value;
			cFile << lineVal << std::endl;
		}
		cFile.flush();
	}
	else
	{
		bRet = false;
	}

	return bRet;
}

CParseCfg::~CParseCfg()
{
}
