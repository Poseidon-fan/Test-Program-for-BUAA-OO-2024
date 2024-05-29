#ifndef REQUEST_H
#define REQUEST_H
#pragma once

enum class Type {
	ARRIVE,
	OPEN,
	CLOSE,
	IN,
	OUT
};

class Request
{
protected:
	Type type;  // 操作类型
	int elevatorID;  // 电梯的ID
	int curFloor;  // 当前层数
public:
	Type getType();
	int getElevatorId();
	int getCurFloor();
	virtual ~Request() {}
	

};
#endif // !REQUEST_H


