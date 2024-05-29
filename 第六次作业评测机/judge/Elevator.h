#ifndef ELEVATOR_H
#define ELEVATOR_H

#pragma once
#include <unordered_map>

#include "Person.h"
#include "Reset.h"

class Elevator
{
private:
	int id;
	int capacity;
	int curFloor;
	double speed;
	bool isOpen;

	std::unordered_map<int, Person*> passengers;  // 乘客
	
	std::pair<bool, double> accept;  // 是否接受了reset——接受时的时间戳
	Reset* reset;  // 接受到的reset
	int step;  // 接受了reset之后走了多少步
	bool isBgein;  // 是否开始reset

public:
	Elevator(int id);
	int getCurFloor();
	void setFloor(int floor);
	std::pair<bool, double> getAccept();
	void setAccept(bool p, double q);
	int getStep();
	void setStep(int step);
	bool getIsOpen();
	void setIsOpen(bool flag);
	int getPassengersNum();
	void addPassenger(Person* person);
	bool hasPassenger(int id);
	int getCapacity();
	void removePassenger(int id);
	void setReset(Reset* r);
	void setIsBegin(bool flag);
	void setCapacity(int c);
	Reset* getReset();
	bool getIsBegin();
	std::unordered_map<int, Person*>& getPassengers();
};

#endif // !ELEVATOR_H


