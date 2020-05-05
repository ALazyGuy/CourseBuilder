#include "MenuController.h"
#include <iterator>

void MenuController::registerItem(std::string msg, std::string id,  bool isAdmin){
	items[msg] = isAdmin;
	IDs[msg] = id;
}

std::string MenuController::generateAsk(){
	std::string result = "\tint choice = -1;\n\twhile(true){\n\t\tcout << \"Item's for admin only marked with $\" << endl;\n";
	int d = 1;

	for(std::map<std::string, bool>::iterator it = items.begin(); it != items.end(); it++){
		result += "\t\tcout << \"" + (it->second ? std::string("$ ") : std::string("  ")) + std::to_string(d++) + ")" + it->first + "\" << endl;\n";
	}

	d = 1;
	result += "\n\t\tcout << \"Enter chosen item number: \";\n\t\tcin >> choice;\n";

	for(std::map<std::string, bool>::iterator it = items.begin(); it != items.end(); it++){
		result += (d++ != 1 ? "\t\telse " : "\t\t") + std::string("if(choice == ") + std::to_string(d) + ") " + IDs[it->first] + "();\n";
	}

	result += "\t}\n";
	return result;
}

std::string MenuController::generateMethods(){
	std::string result = "";
	for(std::map<std::string, std::string>::iterator it = IDs.begin(); it != IDs.end(); it++){
		result += "\nvoid " + it->second + "(){\n" +(items[it->first] ? std::string("\tif(!checkAdmin()) return;\n") : std::string("")) + "\t//Code here\n}\n\n";
	}

	return result;
}
