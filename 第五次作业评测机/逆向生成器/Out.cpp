#include "Out.h"

Out::Out(int curFloor, int elevatorId, int passengerId)
{
	this->type = Type::OUT;
	this->curFloor = curFloor;
	this->elevatorID = elevatorID;
	this->passengerId = passengerId;
}

int Out::getPassengerId()
{
	return passengerId;
}
