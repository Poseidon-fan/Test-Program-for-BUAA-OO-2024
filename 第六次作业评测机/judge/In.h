#ifndef IN_H
#define IN_H

#pragma once
#include "Log.h"
#include <string>
class In :
    public Log
{
private:
    int curFloor;
    int passengerId;
public:
    In(double time, int curFloor, int elevatorId, int passengerId);
    int getCurFloor();
    int getPassengerId();
    std::string toString() override;
};

#endif // !IN_H


