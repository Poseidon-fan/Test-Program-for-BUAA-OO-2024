#include "Open.h"

Open::Open(double time, int curFloor, int elevatorId)
{
	this->time = time;
	this->curFloor = curFloor;
	this->elevatorId = elevatorId;
	this->type = Type::OPEN;
}

int Open::getCurFloor()
{
	return curFloor;
}

std::string Open::toString()
{
    std::string res = "[";
    res += std::to_string(time);
    res += "]";
    res += "OPEN-";
    res += std::to_string(curFloor);
    res += "-";
    res += std::to_string(elevatorId);
    return res;
}
