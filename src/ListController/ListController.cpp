#include "ListController.h"

ListController::ListController(bool isVector){
	this->isVector = isVector;
}

void ListController::write(){
	if(isVector) return;
}
