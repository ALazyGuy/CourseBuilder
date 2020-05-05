#include "FilesController.h"
#include <iterator>

FilesController::FilesController(std::string filename){
	this->filename = filename;
}

std::string FilesController::getLoadSaveFunctions(EntityController* ec){
	if(filename.empty()) return std::string("");
	std::string result = "void save(){\n\tofstream out(\"" + filename + "\");\n\t" + ec->getName() + "* current = nullptr;\n\tint counter = 1;\n";
	result += "\tfor(int d = 0; d < entities.size(); d++){\n";
	result += "\t\tcurrent = entities[d];\n\t\tout << ";
	int counter = 1;
	for(std::map<std::string, std::string>::iterator it = ec->getFields().begin(); it != ec->getFields().end(); it++){
		result += std::string("current->get") + (char)toupper(it->first[0]) + it->first.substr(1) + (counter++ != ec->getSize() ? "() << " : "() << (counter++ != entities.size() ? \"\\n\" : \"\");\n");
	}
	result += "\t}\n\tout.close();\n}";
	return result;
}
