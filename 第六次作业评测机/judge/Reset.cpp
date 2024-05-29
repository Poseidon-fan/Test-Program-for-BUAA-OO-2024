#include "Reset.h"

Reset::Reset(double time, Type type, int elevatorId, int capacity, double speed)
{
	this->time = time;
	this->type = type;
	this->elevatorId = elevatorId;
	this->capacity = capacity;
	this->speed = speed;
	
}

bool Reset::equal(const Reset& r)
{
	return type == r.type &&
		elevatorId == r.elevatorId &&
		capacity == r.capacity &&
		(speed - r.speed < 0.01);
}

int Reset::getCapacity()
{
	return capacity;
}

double Reset::getSpeed()
{
	return speed;
}

std::string Reset::toString()
{
    std::string res = "[";
    res += std::to_string(time);
    res += "]";
	if (type == Type::RESET_ACCEPT) {
		res += "RESET_ACCEPT-";
		res += std::to_string(elevatorId);
		res += "-";
		res += std::to_string(capacity);
		res += "-";
		res += std::to_string(speed);

	}
	else if (type == Type::RESET_BEGIN) {
		res += "RESET_BEGIN-";
		res += std::to_string(elevatorId);
	}
	else {
		res += "RESET_END-";
		res += std::to_string(elevatorId);
	}
    return res;
}
