#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <filesystem>
#include <iostream>

#include "ConfigMgr.h"


ConfigMgr& ConfigMgr::operator=(const ConfigMgr& src)
{
	if (&src == this) {
		return *this;
	}

	this->_config_map = src._config_map;
	return *this;
}

ConfigMgr::~ConfigMgr()
{
	_config_map.clear();
}

SectionInfo ConfigMgr::operator[](const std::string& section)
{
	if (_config_map.find(section) == _config_map.end()) {
		return SectionInfo();
	}
	return _config_map[section];
}

ConfigMgr::ConfigMgr(){
	// ��ȡ��ǰ����Ŀ¼  
	std::filesystem::path current_path = std::filesystem::current_path();
	// ����config.ini�ļ�������·��  
	std::filesystem::path config_path = current_path / "config.ini";
	std::cout << "Config path: " << config_path << std::endl;

	// ʹ��Boost.PropertyTree����ȡINI�ļ�  
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(config_path.string(), pt);


	// ����INI�ļ��е�����section  
	for (const auto& section_pair : pt) {
		const std::string& section_name = section_pair.first;
		const boost::property_tree::ptree& section_tree = section_pair.second;

		// ����ÿ��section�����������е�key-value��  
		std::map<std::string, std::string> section_config;
		for (const auto& key_value_pair : section_tree) {
			const std::string& key = key_value_pair.first;
			const std::string& value = key_value_pair.second.get_value<std::string>();
			section_config[key] = value;
		}
		SectionInfo sectionInfo;
		sectionInfo._section_datas = section_config;
		// ��section��key-value�Ա��浽config_map��  
		_config_map[section_name] = sectionInfo;
	}

	// ������е�section��key-value��  
	for (const auto& section_entry : _config_map) {
		const std::string& section_name = section_entry.first;
		SectionInfo section_config = section_entry.second;
		std::cout << "[" << section_name << "]" << std::endl;
		for (const auto& key_value_pair : section_config._section_datas) {
			std::cout << key_value_pair.first << "=" << key_value_pair.second << std::endl;
		}
	}

}

ConfigMgr::ConfigMgr(const ConfigMgr& src)
{
	this->_config_map = src._config_map;
}

ConfigMgr& ConfigMgr::GetInstance()
{
	static ConfigMgr instance;
	return instance;
}

SectionInfo& SectionInfo::operator=(const SectionInfo& src)
{
	if (&src == this) {
		return *this;
	}

	this->_section_datas = src._section_datas;
	return *this;
}

SectionInfo::SectionInfo(const SectionInfo& src)
{
	_section_datas = src._section_datas;
}

SectionInfo::SectionInfo()
{

}

SectionInfo::~SectionInfo()
{
	_section_datas.clear();
}

std::string SectionInfo::operator[](const std::string& key)
{
	if (_section_datas.find(key) == _section_datas.end()) {
		return "";
	}
	// ����������һЩ�߽���  
	return _section_datas[key];
}
