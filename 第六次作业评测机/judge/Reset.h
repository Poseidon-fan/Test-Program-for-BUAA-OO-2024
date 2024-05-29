#ifndef RESET_H
#define RESET_H

#pragma once
#include "Log.h"
#include <string>
class Reset :
    public Log
{
private:
    int capacity;
    double speed;

public:
    Reset(double time, Type type, int elevatorId, int capacity = 0, double speed = 0);
    bool equal(const Reset& r);
    int getCapacity();
    double getSpeed();
    std::string toString() override;
};

#endif // !RESET_H


