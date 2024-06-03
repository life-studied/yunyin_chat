#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <map>
#include <string>

struct SectionInfo {
	SectionInfo();
	~SectionInfo();
	
	SectionInfo(const SectionInfo& src);
	
	SectionInfo& operator = (const SectionInfo& src);

	std::map<std::string, std::string> _section_datas;
	std::string  operator[](const std::string  &key);
};

class ConfigMgr
{
public:
	~ConfigMgr();
	SectionInfo operator[](const std::string& section);


	ConfigMgr& operator=(const ConfigMgr& src);

	ConfigMgr(const ConfigMgr& src);

	static ConfigMgr& GetInstance();
private:
	ConfigMgr();
	// ´æ´¢sectionºÍkey-value¶ÔµÄmap  
	std::map<std::string, SectionInfo> _config_map;
};

