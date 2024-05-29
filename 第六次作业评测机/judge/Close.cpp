#include "Close.h"

Close::Close(double time, int curFloor, int elevatorId)
{
	this->time = time;
	this->curFloor = curFloor;
	this->elevatorId = elevatorId;
	this->type = Type::CLOSE;
}

int Close::getCurFloor()
{
	return curFloor;
}

std::string Close::toString()
{
    std::string res = "[";
    res += std::to_string(time);
    res += "]";
    res += "CLOSE-";
    res += std::to_string(curFloor);
    res += "-";
    res += std::to_string(elevatorId);
    return res;
}
