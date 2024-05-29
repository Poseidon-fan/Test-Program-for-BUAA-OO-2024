#ifndef OPEN_H
#define OPEN_H

#pragma once
#include "Log.h"
#include <string>
class Open :
    public Log
{
private:
    int curFloor;
public:
    Open(double time, int curFloor, int elevatorId);
    int getCurFloor();
    std::string toString() override;
};

#endif // !OPEN_H


