#pragma once

#include <string>
#include <map>

class MenuController{
private:
	std::map<std::string, bool> items;
	std::map<std::string, std::string> IDs;

public:
	void registerItem(std::string, std::string, bool);
	std::string generateAsk();
	std::string generateMethods();
};
