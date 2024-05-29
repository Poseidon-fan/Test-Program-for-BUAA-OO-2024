#ifndef ARRIVE_H
#define ARRIVE_H

#pragma once
#include "Log.h"
#include <string>
class Arrive :
    public Log
{
private:
    int curFloor;
public:
    Arrive(double time, int curFloor, int elevatorId);
    int getCurFloor();
    std::string toString() override;
};

#endif // !ARRIVE_H


