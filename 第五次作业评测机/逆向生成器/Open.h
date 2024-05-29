#ifndef OPEN_H
#define OPEN_H
#pragma once
#include "Request.h"
class Open :
    public Request
{
public:
    Open(int curFloor, int elevatorId);
};
#endif // !OPEN_H


