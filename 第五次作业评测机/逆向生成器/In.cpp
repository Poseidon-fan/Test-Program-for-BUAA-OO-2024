#include "In.h"

In::In(int curFloor, int elevatorId, int passengerId)
{
	this->type = Type::IN;
	this->curFloor = curFloor;
	this->elevatorID = elevatorID;
	this->passengerId = passengerId;
}

int In::getPassengerId()
{
	return passengerId;
}
