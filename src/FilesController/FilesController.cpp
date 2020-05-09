#include "FilesController.h"
#include <iterator>

FilesController::FilesController(std::string filename){
	this->filename = filename;
}

std::string FilesController::getLoadSaveFunctions(EntityController* ec){

	//save

	if(filename.empty()) return std::string("");
	std::string result = "void save(){\n\tofstream out(\"" + filename + "\");\n\t" + ec->getName() + "* current = nullptr;\n";
	result += "\tfor(int d = 0; d < entities.size(); d++){\n";
	result += "\t\tcurrent = entities[d];\n\t\tout << ";
	for(std::map<std::string, std::string>::iterator it = ec->getFields().begin(); it != ec->getFields().end(); it++){
		result += std::string("current->get") + (char)toupper(it->first[0]) + it->first.substr(1) + "() << ";
	}
	result += "(d + 1 != entities.size() ? \"\\n\" : \"\");\n\t}\n\tout.close();\n}\n\n";

	//load

	result += "void load(){\n\tifstream in(\"" + filename + "\");\n\tif(!in) return;\n";
	for(std::map<std::string, std::string>::iterator it = ec->getFields().begin(); it != ec->getFields().end(); it++){
		result += "\t" + it->second + " " + it->first + ";\n";
	}
	result += "\twhile(!in.eof()){\n\t\tin >> ";
	for(std::map<std::string, std::string>::iterator it = ec->getFields().begin(); it != ec->getFields().end(); it++){
		result += it->first + " >> ";
	}
	result = result.substr(0, result.size() - 4);
	result += ";\n\t\tentities.push_back(new " + ec->getName() + "(";
	for(std::map<std::string, std::string>::iterator it = ec->getFields().begin(); it != ec->getFields().end(); it++){
		result += it->first + ", ";
	}
	result = result.substr(0, result.size() - 2);
	result += "));\n\t}\n\tin.close();\n}";
	return result;
}
