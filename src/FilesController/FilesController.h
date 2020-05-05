#pragma once

#include "../EntityController/EntityController.h"
#include <string>

class FilesController{
private:
	std::string filename;

public:
	FilesController(std::string);
	std::string getLoadSaveFunctions(EntityController*);
};
