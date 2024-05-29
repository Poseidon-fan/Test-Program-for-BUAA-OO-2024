#ifndef IN_H
#define IN_H
#pragma once
#include "Request.h"
class In :
    public Request
{
private:
    int passengerId;
public:
    In(int curFloor, int elevatorId, int passengerId);
    int getPassengerId();
};

#endif // !IN_H

