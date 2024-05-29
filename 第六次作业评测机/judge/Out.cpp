#include "Out.h"

Out::Out(double time, int curFloor, int elevatorId, int passengerId)
{
	this->time = time;
	this->curFloor = curFloor;
	this->elevatorId = elevatorId;
	this->passengerId = passengerId;
	this->type = Type::OUT;
}

int Out::getCurFloor()
{
	return curFloor;
}

int Out::getPassengerId()
{
	return passengerId;
}

std::string Out::toString()
{
    std::string res = "[";
    res += std::to_string(time);
    res += "]";
    res += "OUT-";
    res += std::to_string(passengerId);
    res += "-";
    res += std::to_string(curFloor);
    res += "-";
    res += std::to_string(elevatorId);
    return res;
}
