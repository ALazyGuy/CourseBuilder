#include <iostream>
#include <fstream>

#include "EntityController/EntityController.h"
#include "ListController/ListController.h"
#include "MenuController/MenuController.h"

#define DIR "Result/"

#define START "\nusing namespace std;\n\n"
#define END "\treturn 0;\n}"

std::string startIncludes = "#include <iostream>\n";
std::string mainCode = "";
std::string variables = "";
std::string preMain = "";

bool menuDone = false, typeDone = false, vectorType = false, listDone = false, entityDone = false;

void configureType(EntityController* ec){
	if(!entityDone) return;
	int result;
	std::cout << "Vector(1) or List(2): ";
	std::cin >> result;
	if(result == 1){
		startIncludes += "#include <vector>\n";
		variables += "vector<" + ec->getName() + "*> entities;\n";
		listDone = true;
		vectorType = true;
	}
	typeDone = true;
}

void configureEntities(EntityController *entityController){
	if(entityDone) return;
	std::string name, type, eName;
	std::cout << "Enter entity name: ";
	std::getline(std::cin, eName);
	entityController->init(eName);
	while(true){
		std::cout << "Enter field name(q to exit): ";
		std::getline(std::cin, name);
		if(name == "q") break;
		std::cout << "Enter field type: ";
		std::getline(std::cin, type);
		entityController->registerField(type, name);
	}
	entityController->write(DIR);
	startIncludes += "#include \"" + entityController->getName() + "/" + entityController->getName() + ".h\"\n";
	entityDone = true;
}

void configureMenu(MenuController* mc){
	if(menuDone) return;
	menuDone = true;
	while(true){
		std::string name, id;
		bool isAdmin;
		std::cout << "Enter item name(q for exit): ";
		std::getline(std::cin, name);
		if(name == "q") break;
		std::cout << "Enter item id: ";
		std::getline(std::cin, id);
		std::cout << "For admin only(1 - y, 0 - n): ";
		std::cin >> isAdmin;
		std::cin.ignore();
		mc->registerItem(name, id, isAdmin);
	}
	preMain += mc->generateMethods();
	mainCode += mc->generateAsk();
}

ListController* configureList(){
	ListController* lc = new ListController(vectorType);
	listDone = true;
	lc->write();
	return lc;
}

void build(){
	std::ofstream out(DIR + std::string("Start.cpp"));
	out << startIncludes << std::endl << START << variables << preMain;
	out << "\nint main(){\n";
	out << mainCode;
	out << END;
	out.close();
	std::cout << "Builded successful!" << std::endl;
}

int main(){
	std::system(("rm -rf " + std::string(DIR) + "/*").c_str());
	EntityController* ec = new EntityController();
	ListController* lc = nullptr;
	MenuController* mc = new MenuController();

	int hasAdmin;
	std::cout << "Add admin/user version(1 - y, 0 - n): ";
	std::cin >> hasAdmin;
	if(hasAdmin == 1){
		std::string pass;
		std::cout << "Enter admin password: ";
		std::cin.ignore();
		std::getline(std::cin, pass);
		variables = "#define ADMIN \"ADMIN\"\n#define USER \"USER\"\nstring role;\nstring password=\"" + pass +  "\";\n";
		mainCode = "\tstring pass;\n\tcout << \"Enter admin password: \";\n\tgetline(cin, pass);\n";
		mainCode += "\tif(pass == password){\n\t\trole = ADMIN;\n\t\tcout << \"Logged in as admin\" << endl;\n\t}else{\n";
		mainCode += "\t\trole = USER;\n\t\tcout << \"Logged in as user\" << endl;\n\t}\n";
		preMain = "bool checkAdmin(){\n\tif(role == ADMIN) return true;\n\tcout << \"You must be admin to use this menu item\" << endl;\n\treturn false;\n}\n\n";
	}

	std::string choise;
	int idCounter = 1;
	while(true){
		idCounter = 1;
		std::cout << "Need to configure:" << std::endl;
		std::cout << idCounter++ << ") Cancel and exit" << std::endl;
		std::cout << (menuDone ? "" : "* ") << idCounter++ << ") Configure menu" << std::endl;
		std::cout << (typeDone ? "" : "* ") << idCounter++ << ") Configure type" << std::endl;
		std::cout << (entityDone ? "" : "* ") << idCounter++ << ") Configure entity" << std::endl;
		if(typeDone && !vectorType) std::cout << (listDone ? "" : "* ") << idCounter++ << ") Configure list" << std::endl;
		if(menuDone && typeDone && listDone && entityDone) std::cout << idCounter++ << ") Build" << std::endl;
		std::cout << "Enter item number: ";
		std::getline(std::cin, choise);
		switch(std::atoi(choise.c_str())){
		case 1: return 0;
		case 2: configureMenu(mc); break;
		case 3: configureType(ec); break;
		case 4: configureEntities(ec); break;
		case 5:{
			if(typeDone && !vectorType){
				lc = configureList();
			}else{
				build();
				return 0;
			}
			break;
		}
		case 6:{
			build();
			return 0;
		}
		}
		std::system("clear");
	}
	return 0;
}
