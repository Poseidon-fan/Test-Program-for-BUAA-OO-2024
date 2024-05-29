#ifndef CLOSE_H
#define CLOSE_H

#pragma once
#include "Log.h"
#include <string>
class Close :
    public Log
{
private:
    int curFloor;
public:
    Close(double time, int curFloor, int elevatorId);
    int getCurFloor();
    std::string toString() override;
};


#endif // !CLOSE_H

