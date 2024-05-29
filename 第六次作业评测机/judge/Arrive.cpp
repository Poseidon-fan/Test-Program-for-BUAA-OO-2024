#include "Arrive.h"
#include<iostream>
Arrive::Arrive(double time, int curFloor, int elevatorId)
{
    this->time = time;
    this->curFloor = curFloor;
    this->elevatorId = elevatorId;
    this->type = Type::ARRIVE;
   
}

int Arrive::getCurFloor()
{
    return curFloor;
}

std::string Arrive::toString()
{
    std::string res = "[";
    res += std::to_string(time);
    res += "]";
    res += "ARRIVE-";
    res += std::to_string(curFloor);
    res += "-";
    res += std::to_string(elevatorId);
    return res;
}
