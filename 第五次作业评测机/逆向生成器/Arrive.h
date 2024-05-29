#ifndef ARRIVE_H
#define ARRIVE_H
#pragma once
#include "Request.h"
class Arrive :
    public Request
{
public:
    Arrive(int curFloor, int elevatorID);

};
#endif // !ARRIVE_H


