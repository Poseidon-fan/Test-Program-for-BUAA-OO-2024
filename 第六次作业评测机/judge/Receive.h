#ifndef RECEIVE_H
#define RECEIVE_H

#pragma once
#include "Log.h"
#include <string>
class Receive :
    public Log
{
private:
    int passengerId;
public:
    Receive(double time, int elevatorId, int passengerId);
    int getPassengerId();
    std::string toString() override;
};

#endif // !RECEIVE_H


