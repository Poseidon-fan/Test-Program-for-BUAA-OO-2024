#ifndef OUT_H
#define OUT_H
#pragma once
#include "Request.h"
class Out :
    public Request
{
private:
    int passengerId;
public:
    Out(int curFloor, int elevatorId, int passengerId);
    int getPassengerId();
};

#endif // !OUT_H

