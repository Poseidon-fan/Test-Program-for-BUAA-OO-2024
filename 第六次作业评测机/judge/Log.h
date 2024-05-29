#ifndef LOG_H
#define LOG_H

#pragma once
#include <string>

enum class Type {
	ARRIVE, OPEN, CLOSE, IN, OUT, RESET_ACCEPT, RESET_BEGIN, RESET_END, RECEIVE
};

class Log
{
protected:
	double time;
	Type type;
	int elevatorId;
public:
	double getTime();
	Type getType();
	int getElevatorId();
	//virtual ~Log() = 0;
	virtual std::string toString() = 0;
};

#endif // !LOG_H


