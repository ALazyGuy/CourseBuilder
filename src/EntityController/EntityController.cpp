#include "EntityController.h"
#include <iterator>
#include <fstream>

void EntityController::init(std::string name){
	this->name = name;
	this->size = 0;
}

void EntityController::registerField(std::string type, std::string name){
	fields[name] = type;
	size++;
}

std::string EntityController::getName(){
	return name;
}

void EntityController::write(std::string directory){
	std::system(("mkdir " + directory + name).c_str());
	std::ofstream headerOut(directory + name + "/" + name + ".h");
	std::ofstream sourceOut(directory + name + "/" + name + ".cpp");
	sourceOut << "#include \"" << name << ".h\"\n";
	headerOut << "#pragma once\n\n#include <string>\n\nusing namespace std;\nclass " << name << "{\nprivate:\n";
	for(std::map<std::string, std::string>::iterator it = fields.begin(); it != fields.end(); it++){
		headerOut << "\t" << it->second << " " << it->first << ";\n";
	}
	int counter = 1;
	headerOut << "public:\n";
	headerOut << "\t" << name << "(";
	sourceOut << name << "::" << name << "(";
	for(std::map<std::string, std::string>::iterator it = fields.begin(); it != fields.end(); it++){
		headerOut << it->second << (counter != size ? ", " : "");
		sourceOut << it->second << " " << it->first << (counter++ != size ? ", " : "");
	}
	headerOut << ");\n";
	sourceOut << "){\n";

	for(std::map<std::string, std::string>::iterator it = fields.begin(); it != fields.end(); it++){
		sourceOut << "\tthis->" << it->first << " = " << it->first << ";\n";
	}
	sourceOut << "}\n\n";

	for(std::map<std::string, std::string>::iterator it = fields.begin(); it != fields.end(); it++){
		headerOut << "\t" << it->second << " get" << (char)std::toupper(it->first[0]) << it->first.substr(1) << "();\n";
		headerOut << "\tvoid set" << (char)std::toupper(it->first[0]) << it->first.substr(1) << "(" << it->second << ");\n";
		sourceOut << it->second << " " << name << "::get" << (char)std::toupper(it->first[0]) << it->first.substr(1) << "(){\n\treturn " << it->first << ";\n}\n";
		sourceOut << "void " << name << "::set" << (char)std::toupper(it->first[0]) << it->first.substr(1) << "(" << it->second << " " << it->first << "){\n\tthis->"
				<< it->first << " = " << it->first <<";\n}\n";
	}

	headerOut << "};";
}

std::map<std::string, std::string> EntityController::getFields(){
	return fields;
}

int EntityController::getSize(){
	return size;
}
