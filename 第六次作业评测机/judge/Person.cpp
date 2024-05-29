#include "Person.h"
#include<iostream>

Person::Person(int id, int departure, int destination)
{
	this->id = id;
	this->departure = departure;
	this->destination = destination;
	this->curFloor = departure;
	this->targetElevatorId = 0;
	this->isIn = false;
}

bool Person::setReceived(int elevatorId)
{
	//std::cout << elevatorId << std::endl;
	if (targetElevatorId != 0) return false;
	this->targetElevatorId = elevatorId;
	return true;
}

void Person::setFloor(int floor)
{
	this->curFloor = floor;
}

bool Person::vertifyFloorDestination()
{
	return curFloor == destination;
}

int Person::getTargetElevatorId()
{
	return targetElevatorId;
}

void Person::setTargetElevatorId(int id)
{
	this->targetElevatorId = id;
}

int Person::getId()
{
	return id;
}

bool Person::getIsIn()
{
	return isIn;
}

void Person::setIsIn(bool flag)
{
	isIn = flag;
}

int Person::getCurFloor()
{
	return curFloor;
}
