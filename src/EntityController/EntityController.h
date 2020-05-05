#pragma once

#include <string>
#include <map>

class EntityController{
private:
	std::string name;
	std::map<std::string, std::string> fields;

public:
	void init(std::string);
	std::string getName();
	void registerField(std::string, std::string);
	void write(std::string);
};
