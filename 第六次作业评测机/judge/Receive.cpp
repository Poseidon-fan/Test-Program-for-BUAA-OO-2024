#include "Receive.h"

Receive::Receive(double time, int elevatorId, int passengerId)
{
	this->time = time;
    this->type = Type::RECEIVE;
	this->elevatorId = elevatorId;
	this->passengerId = passengerId;
}

int Receive::getPassengerId()
{
    return passengerId;
}

std::string Receive::toString()
{
    std::string res = "[";
    res += std::to_string(time);
    res += "]";
    res += "RECEIVE-";
    res += std::to_string(passengerId);
    res += "-";
    res += std::to_string(elevatorId);
    return res;
}
