#ifndef PERSON_H
#define PERSON_H

#pragma once
class Person
{
private:
	int id;
	int departure;
	int destination;
	int curFloor;
	int targetElevatorId;
	bool isIn;
public:
	Person(int id, int departure, int destination);
	bool setReceived(int elevatorId);
	void setFloor(int floor);
	bool vertifyFloorDestination();
	int getTargetElevatorId();
	void setTargetElevatorId(int id);
	int getId();
	bool getIsIn();
	void setIsIn(bool flag);
	int getCurFloor();
};


#endif // !PERSON_H

