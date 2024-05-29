#include "Arrive.h"

Arrive::Arrive(int curFloor, int elevatorID)
{
	this->type = Type::ARRIVE;
	this->curFloor = curFloor;
	this->elevatorID = elevatorID;
}
