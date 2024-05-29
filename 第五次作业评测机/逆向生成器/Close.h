#ifndef CLOSE_H
#define CLOSE_H
#pragma once
#include "Request.h"
class Close :
    public Request
{
public:
    Close(int curFloor, int elevatorId);
};

#endif // !CLOSE_H

