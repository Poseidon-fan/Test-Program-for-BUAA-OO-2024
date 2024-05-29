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

	std::unordered_map<int, Person*> passengers;  // �˿�
	
	std::pair<bool, double> accept;  // �Ƿ������reset��������ʱ��ʱ���
	Reset* reset;  // ���ܵ���reset
	int step;  // ������reset֮�����˶��ٲ�
	bool isBgein;  // �Ƿ�ʼreset

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


