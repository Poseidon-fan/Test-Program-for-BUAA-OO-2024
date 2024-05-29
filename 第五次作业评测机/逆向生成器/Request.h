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
	Type type;  // ��������
	int elevatorID;  // ���ݵ�ID
	int curFloor;  // ��ǰ����
public:
	Type getType();
	int getElevatorId();
	int getCurFloor();
	virtual ~Request() {}
	

};
#endif // !REQUEST_H


