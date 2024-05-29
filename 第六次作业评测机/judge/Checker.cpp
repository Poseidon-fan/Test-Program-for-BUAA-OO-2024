#include "Checker.h"


void Checker::parseInput(const std::string& input_path)
{
	extern std::vector<std::string> split_string(const std::string & s, char delimiter);
	std::ifstream file(input_path);

	std::string log;
	while (std::getline(file, log)) {
		int i = 1;
		while (log[i] != ']') i++; i++;

		std::vector<std::string> tokens = split_string(log.substr(i), '-');
		if (tokens[0] == "RESET") {
			int elevatorId = std::stoi(tokens[2]);
			int capacity = std::stoi(tokens[3]);
			double speed = std::stoi(tokens[4]);
			resets.push_back(std::pair<Reset*, bool>(new Reset(0, Type::RESET_ACCEPT, elevatorId, capacity, speed), false));

		}
		else {
			int passengerId = std::stoi(tokens[0]);
			int departure = std::stoi(tokens[2]);
			int destinantion = std::stoi(tokens[4]);
			persons[passengerId] = new Person(passengerId, departure, destinantion);
		}
	}

	file.close();
}

Checker::Checker(const std::string& input_path, const std::string& output_path, const std::string& error_path)
{
	this->error_path = error_path;
	this->parser = new Parser(output_path);
	for (int i = 1; i <= 6; i++) {
		elevators[i] = new Elevator(i);
	}
	parseInput(input_path);
}

Checker::~Checker()
{
	delete parser;
	for (const auto& pair : persons) {
		delete pair.second;
	}

	for (std::pair<Reset*, bool> p : resets) {
		delete p.first;
	}

	for (const auto& pair : elevators) {
		delete pair.second;
	}
}

void Checker::writeError(const std::string& error)
{
	std::ofstream file(error_path);
	file << error;
	file.close();
}

bool Checker::checkResets()
{
	for (Log* log : *(parser->getLogStream())) {
		if (log->getType() == Type::RESET_ACCEPT) {
			bool flag = false;
			for (std::pair<Reset*, bool> p : resets) {
				if (p.first->equal(*dynamic_cast<Reset*>(log)) && p.second == false) {
					p.second = true;
					flag = true;
					break;
				}
			}
			if (!flag) {
				std::ofstream file(error_path);
				file << "The reset request " + log->toString() + "didn't input but is accepted";
				file.close();
				return false;
			}
		}	
	}

	for (std::pair<Reset*, bool> p : resets) {
		if (p.second == false) {
			std::ofstream file(error_path);
			file << "The reset request " + p.first->toString() + "didn't been accepted";
			file.close();
			return false;
		}
		return true;
	}
}

bool Checker::finalCheck()
{
	for (const auto& pair : persons) {
		Person* person = pair.second;

		if (person->getIsIn()) {
			writeError("Person with the id of " + std::to_string(person->getId()) + " didn't get out of the elevator in the end");
			return false;
		}

		if (!person->vertifyFloorDestination()) {
			writeError("Person with the id of " + std::to_string(person->getId()) + "didn't reach the destinantion");
			return false;
		}
	}

	for (const auto& pair : elevators) {
		// ����Ƿ����
		if (pair.second->getIsOpen()) {
			writeError("The elevator with the id of " + std::to_string(pair.first) + " didn't close in the end");
			return false;
		}

		// ����Ƿ�û�г˿�
		if (!pair.second->getPassengers().empty()) {
			for (const auto& p : pair.second->getPassengers()) {
				writeError("The elevator with the id of " + std::to_string(pair.first) + " conatins the passeger with the id of " + std::to_string(p.first) + " in the end");
				return false;
			}
		}

		// ����Ƿ��е��ݻ���reset
		if (pair.second->getIsBegin()) {
			writeError("The elevator with the id of " + std::to_string(pair.first) + " is still resetting in the end");
			return false;
		}
	}
	return true;
}

bool Checker::check()
{
	for (Log* log : *(parser->getLogStream())) {
		//std::cout << log->toString() << std::endl;
		Elevator* elevator = elevators[log->getElevatorId()];
		switch (log->getType()) {
			case Type::ARRIVE: {
				Arrive* a = dynamic_cast<Arrive*>(log);
				int floor = a->getCurFloor();

				// ��Ծ��¥�㲻�Ϸ�
				if (abs(floor - elevator->getCurFloor()) != 1) {
					writeError(a->toString() + "  You jump from " + std::to_string(elevator->getCurFloor()) + " to " + std::to_string(floor));
					return false;
				}

				// �����ݼ����ڵĳ˿�¥�����
				elevator->setFloor(floor);

				// �жϵ�ǰ�Ƿ�������
				if (elevator->getAccept().first == true) {
					int s = elevator->getStep();
					if (s == 2) {
						writeError(a->toString() + "  You moved more than 2 times after accepting reset");
						return false;
					}
					elevator->setStep(s + 1);
				}
				break;
			}
				
			case Type::OPEN: {
				Open* o = dynamic_cast<Open*>(log);

				// �ж����ο��Ų��Ϸ�
				if (elevator->getIsOpen()) {
					writeError(o->toString() + "  You opened doors for twice");
					return false;
				}

				elevator->setIsOpen(true);
				break;
			}				
			case Type::CLOSE: {
				Close* c = dynamic_cast<Close*>(log);

				// �ж��ظ�����
				if (!elevator->getIsOpen()) {
					writeError(c->toString() + "  You closed the door when iti's already closed");
					return false;
				}

				elevator->setIsOpen(false);
				break;
			}	
			case Type::IN: {
				In* i = dynamic_cast<In*>(log);

				int floor = i->getCurFloor();
				int passengerId = i->getPassengerId();

				// ����ϳ�¥�����ȷ��
				if (floor != elevator->getCurFloor()) {
					writeError(i->toString() + "  The passenger got in the elevator on " + std::to_string(elevator->getCurFloor()) + "-th floor when he's actually on" + std::to_string(floor));
					return false;
				}

				// ����Ƿ��������

				// ����Ƿ񱻷����
				if (persons[passengerId]->getTargetElevatorId() == 0) {
					writeError(i->toString() + "  The passenger hasn't been received");
					return false;
				}

				// ����Ƿ������ȷ
				if (persons[passengerId]->getTargetElevatorId() != i->getElevatorId()) {
					writeError(i->toString() + "  The passenger gets on the wrong elevator");
					return false;
				}

				// ����Ƿ��Ѿ��ϵ���
				if (persons[passengerId]->getIsIn()) {
					writeError(i->toString() + "  The passenger has been in the elevator");
					return false;
				}

				// ����Ƿ���
				if (elevator->getPassengersNum() == elevator->getCapacity()) {
					writeError(i->toString() + "  Overload!");
					return false;
				}

				persons[passengerId]->setIsIn(true);
				elevator->addPassenger(persons[passengerId]);

				break;
			}				
			case Type::OUT: {
				Out* o = dynamic_cast<Out*>(log);

				int floor = o->getCurFloor();
				int passengerId = o->getPassengerId();

				// ��鵱ǰ�Ƿ��ڵ�����
				if (!elevator->hasPassenger(passengerId)) {
					writeError(o->toString() + "  The passenger isn't in the elevator");
					return false;
				}

				// ����µ��ݵ�¥���Ƿ���ȷ
				if (persons[passengerId]->getCurFloor() != floor) {
					writeError(o->toString() + "  The passenger gets off on  " + std::to_string(floor) + "-th floor when he's actually on the  " + std::to_string(persons[passengerId]->getCurFloor()) + "-th");
					return false;
				}

				elevator->removePassenger(passengerId);
				persons[passengerId]->setIsIn(false);
				persons[passengerId]->setTargetElevatorId(0);

				break;
			}				
			case Type::RECEIVE: {
				Receive* r = dynamic_cast<Receive*>(log);
				int passengerId = r->getPassengerId();
				Person* person = persons[passengerId];

				// ����Ƿ��Ѿ���receive��
				if (person->getTargetElevatorId() != 0) {
					writeError(r->toString() + "  The passenger has been received");
					return false;
				}

				person->setReceived(r->getElevatorId());

				break;
			}				
			case Type::RESET_ACCEPT: {
				Reset* r = dynamic_cast<Reset*>(log);
				
				// ����Ƿ��Ѿ���������
				if (elevator->getAccept().first == true) {
					writeError(r->toString() + "  The reset request has been accepted");
					return false;
				}

				elevator->setAccept(true, r->getTime());
				elevator->setReset(r);

				break;
			}
			case Type::RESET_BEGIN: {
				Reset* r = dynamic_cast<Reset*>(log);

				// ����Ƿ�Accept
				if (elevator->getAccept().first == false) {
					writeError(r->toString() + "  The reset request begins before accepting");
					return false;
				}

				// ����Ƿ��Ѿ�begin��
				if (elevator->getIsBegin()) {
					writeError(r->toString() + "  The reset request has begun");
					return false;
				}

				// ���begin��ʱ���Ƿ��г˿�
				if (!elevator->getPassengers().empty()) {
					writeError(r->toString() + "  When the elevator reset started, there were still passengers inside");
					return false;
				}

				elevator->setStep(0);
				elevator->setIsBegin(true);
				for (const auto& pair : persons) {
					Person* p = pair.second;
					if (p->getTargetElevatorId() == r->getElevatorId()) {
						p->setTargetElevatorId(0);
					}
				}

				break;
			}
			case Type::RESET_END: {
				Reset* r = dynamic_cast<Reset*>(log);
				double time = r->getTime();

				// ����Ƿ�begin
				if (!elevator->getIsBegin()) {
					writeError(r->toString() + "  The reset request is end before beginning");
					return false;
				}

				// ������accept��ʱ����Ƿ�С��5s
				if (abs(time - elevator->getAccept().second) >= 5) {
					writeError(r->toString() + "  The gap between accept and begin is more than 5s");
					return false;
				}

				elevator->setCapacity(elevator->getReset()->getCapacity());
				elevator->setAccept(false, 0);
				elevator->setIsBegin(false);

				break;
			} 
				
		}
	}
	
	
	return finalCheck();
}
