#include "In.h"

In::In(double time, int curFloor, int elevatorId, int passengerId)
{
	this->time = time;
	this->curFloor = curFloor;
	this->elevatorId = elevatorId;
	this->passengerId = passengerId;
	this->type = Type::IN;
}

int In::getCurFloor()
{
	return curFloor;
}

int In::getPassengerId()
{
	return passengerId;
}

std::string In::toString()
{
    std::string res = "[";
    res += std::to_string(time);
    res += "]";
    res += "IN-";
    res += std::to_string(passengerId);
    res += "-";
    res += std::to_string(curFloor);
    res += "-";
    res += std::to_string(elevatorId);
    return res;
}
