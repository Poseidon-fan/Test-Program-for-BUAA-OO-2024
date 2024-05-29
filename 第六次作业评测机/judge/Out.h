#ifndef OUT_H
#define OUT_H

#pragma once
#include "Log.h"
#include <string>
class Out :
    public Log
{
private:
    int curFloor;
    int passengerId;
public:
    Out(double time, int curFloor, int elevatorId, int passengerId);
    int getCurFloor();
    int getPassengerId();
    std::string toString() override;
};

#endif // !OUT_H

