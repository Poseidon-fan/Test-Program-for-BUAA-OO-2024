#include "Close.h"

Close::Close(int curFloor, int elevatorId)
{
	this->type = Type::CLOSE;
	this->curFloor = curFloor;
	this->elevatorID = elevatorID;
}
