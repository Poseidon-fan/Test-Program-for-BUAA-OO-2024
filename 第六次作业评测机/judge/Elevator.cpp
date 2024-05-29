#include "Elevator.h"

Elevator::Elevator(int id)
{
	this->id = id;
	this->capacity = 6;
	this->curFloor = 1;
	this->speed = 0.4;
	this->isOpen = false;
	this->accept.first = false;
	this->step = 0;
	this->isBgein = false;
}

int Elevator::getCurFloor()
{
	return curFloor;
}

void Elevator::setFloor(int floor)
{
	curFloor = floor;
	for (const auto& pair : passengers) {
		pair.second->setFloor(curFloor);
	}
}

std::pair<bool, double> Elevator::getAccept()
{
	return accept;
}

void Elevator::setAccept(bool p, double q)
{
	accept.first = p;
	accept.second = q;
}

int Elevator::getStep()
{
	return step;
}

void Elevator::setStep(int step)
{
	this->step = step;
}

bool Elevator::getIsOpen()
{
	return isOpen;
}

void Elevator::setIsOpen(bool flag)
{
	isOpen = flag;
}

int Elevator::getPassengersNum()
{
	return passengers.size();
}

void Elevator::addPassenger(Person* person)
{
	passengers[person->getId()] = person;
}

bool Elevator::hasPassenger(int id)
{
	return passengers.find(id) != passengers.end();
}

int Elevator::getCapacity()
{
	return capacity;
}

void Elevator::removePassenger(int id)
{
	passengers.erase(id);
}

void Elevator::setReset(Reset* r)
{
	this->reset = r;
}

void Elevator::setIsBegin(bool flag)
{
	isBgein = flag;
}

void Elevator::setCapacity(int c)
{
	this->capacity = c;
}

Reset* Elevator::getReset()
{
	return reset;
}

bool Elevator::getIsBegin()
{
	return isBgein;
}

std::unordered_map<int, Person*>& Elevator::getPassengers()
{
	return passengers;
}

