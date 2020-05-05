#pragma once

#include <string>
#include <map>

class EntityController{
private:
	std::string name;
	int size;
	std::map<std::string, std::string> fields;

public:
	void init(std::string);
	std::map<std::string, std::string> getFields();
	std::string getName();
	int getSize();
	void registerField(std::string, std::string);
	void write(std::string);
};
