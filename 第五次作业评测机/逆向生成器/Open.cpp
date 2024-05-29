#include "Open.h"

Open::Open(int curFloor, int elevatorId)
{
	this->type = Type::OPEN;
	this->curFloor = curFloor;
	this->elevatorID = elevatorID;
}
