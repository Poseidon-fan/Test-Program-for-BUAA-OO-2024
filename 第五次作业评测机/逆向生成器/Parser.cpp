#include "Parser.h"
#include <algorithm>
// 以delimiter分割字符串，并返回其token列表
std::vector<std::string> split_string(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	while ((pos = s.find(delimiter, prev)) != std::string::npos) {
		tokens.push_back(s.substr(prev, pos - prev));
		prev = pos + 1;
	}
	// 添加最后一个部分（如果存在）  
	if (prev < s.length()) {
		tokens.push_back(s.substr(prev));
	}
	return tokens;
}

// 排序函数，对逆向的输出进行排序
bool cmp(std::pair<int, std::string>& a, std::pair<int, std::string>& b) {
	return a.first < b.first;
}

void Parser::addRequest(const std::string& input)
{
	Type type;
	int curFloor, passengerId, elevatorId;
	int i = 1;

	// 识别type
	while (input[i] != ']') i++;
	switch (input[i + 1]) {
		case 'A':
			type = Type::ARRIVE;
			break;
		case 'O':
			if (input[i + 2] == 'P') type = Type::OPEN;
			else type = Type::OUT;
			break;
		case 'C':
			type = Type::CLOSE;
			break;
		case 'I':
			type = Type::IN;
			break;
		default:
			std::cout << "Error when parsing input: " << input << std::endl;
	}

	while (input[i] != '-') i++;
	i++;
	std::vector<std::string> tokens = split_string(input.substr(i), '-');
	if (tokens.size() == 3) {
		passengerId = std::stoi(tokens[0]);
		curFloor = std::stoi(tokens[1]);
		elevatorId = std::stoi(tokens[2]);
	}
	else if (tokens.size() == 2) {
		curFloor = std::stoi(tokens[0]);
		elevatorId = std::stoi(tokens[1]);
	}
	else std::cout << "Error when spliting input" << std::endl;

	// 解析输入完成，构建对象
	Request *request = NULL;
	switch (type) {
		case Type::ARRIVE:
			request = new Arrive(curFloor, elevatorId);
			elevators[elevatorId].push_back(request);
			break;
		case Type::OPEN:
			request = new Open(curFloor, elevatorId);
			elevators[elevatorId].push_back(request);
			break;
		case Type::CLOSE:
			request = new Close(curFloor, elevatorId);
			elevators[elevatorId].push_back(request);
			break;
		case Type::IN:
			request = new In(curFloor, elevatorId, passengerId);
			elevators[elevatorId].push_back(request);
			break;
		case Type::OUT:
			request = new Out(curFloor, elevatorId, passengerId);
			elevators[elevatorId].push_back(request);
			break;
		default:
			std::cout << "Error when constructing elevator" << std::endl;
	}
}

Parser::Parser(std::vector<int> eleIds)
{
	for (int i : eleIds) {
		std::vector<Request*> elevator;
		elevators[i] = elevator;
	}
}

Parser::~Parser()
{
	for (const auto& t : elevators) {
		for (Request* request : t.second) {
			delete request;
		}
	}
}

void Parser::parseSequences(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cout << "Error when opening the file" << std::endl;
		return;
	}
	std::string input;
	while (std::getline(file, input)) {
		addRequest(input);
	}
	file.close();
}

bool checkElevatorProcessValidity(const std::vector<Request*>& elevator, int elevatorId) {
	extern int minFloor;
	extern int maxFloor;
	extern int capacity;
	int curNum = 0;  // 当前电梯内乘客数量
	int curFloor = 1;  // 当前电梯运行到的楼层
	bool isOpen = false;  // 是否开门

	for (Request* request : elevator) {
		int targetFloor = request->getCurFloor();
		switch (request->getType()) {
		case Type::ARRIVE:
			if (!(targetFloor == curFloor + 1 || targetFloor == curFloor - 1)) {
				printf("Behavior Error! The elevator with the id of %d jump from %d-th floor to %d-th floor\n", elevatorId, curFloor, targetFloor);
				return false;
			}

			if (targetFloor < minFloor || targetFloor > maxFloor) {
				printf("Behavior Error! The elevator with the id of %d reached the illegal floor %d\n", elevatorId, targetFloor);
				return false;
			}

			curFloor = targetFloor;
			break;
		case Type::OPEN:
			if (curFloor != targetFloor) {
				printf("Behavior Error! The elevator with the id of %d opened door on %d-th floor when it is actually on %d-th floor\n", elevatorId, targetFloor, curFloor);
				return false;
			}

			if (isOpen) {
				printf("Behavior Error! The elevator with the id of %d re-opened on %d-th floor\n", elevatorId, curFloor);
				return false;
			}
			isOpen = true;
			break;
		case Type::CLOSE:
			if (curFloor != targetFloor) {
				printf("Behavior Error! The elevator with the id of %d closed door on %d-th floor when it is actually on %d-th floor\n", elevatorId, targetFloor, curFloor);
				return false;
			}

			if (!isOpen) {
				printf("Behavior Error! The elevator with the id of %d re-closed on %d-th floor\n", elevatorId, curFloor);
				return false;
			}
			isOpen = false;
			break;
		case Type::IN:
			curNum++;
			if (curFloor != targetFloor) {
				printf("Behavior Error! The elevator with the id of %d received a passenger who is actually on %d-th floor on %d-th floor \n", elevatorId, targetFloor, curFloor);
				return false;
			}
			if (curNum > capacity) {
				printf("Behavior Error! The elevator with the id of %d carries passengers beyong its capacity\n", elevatorId);
				return false;
			}
			break;
		case Type::OUT:
			curNum--;
			if (curFloor != targetFloor) {
				printf("Behavior Error! The elevator with the id of %d dropped a passenger who is actually on %d-th floor on %d-th floor \n", elevatorId, targetFloor, curFloor);
				return false;
			}
			break;
		default:
			break;
		}
	}
	return true;
}


bool Parser::checkProcessValidity()
{
    std::vector<std::pair<int, std::string>> reverseChart;
	for (const auto& t : elevators) {
		int elevatorId = t.first;
		std::vector<Request*> elevator = t.second;
		if (!checkElevatorProcessValidity(elevator, elevatorId)) return false;
		std::unordered_map<int, std::vector<Request*>> passengers;
		for (Request* request : elevator) {
			if (request->getType() == Type::ARRIVE || request->getType() == Type::OPEN || request->getType() == Type::CLOSE) continue;
			if (request->getType() == Type::IN) {
				In* tmp = dynamic_cast<In*> (request);
				passengers[tmp->getPassengerId()].push_back(tmp);
			}
			else if (request->getType() == Type::OUT) {
				Out* tmp = dynamic_cast<Out*> (request);
				passengers[tmp->getPassengerId()].push_back(tmp);
			}
		}

		for (const auto& t : passengers) {
			int passengerId = t.first;
			std::vector<Request*> table = t.second;
			if (table.size() != 2) {
				printf("Behavior Error! The passenger with the id of %d in or out for %d times\n", passengerId, table.size());
				return false;
			}

			if (table[0]->getType() != Type::IN || table[1]->getType() != Type::OUT) {
				printf("Behavior Error! The passenger with the id of %d didn't come in first or go out second\n", passengerId);
				return false;
			}
			std::string log = "";
			log += std::to_string(passengerId);
			log += "-FROM-";
			log += std::to_string(table[0]->getCurFloor());
			log += "-TO-";
			log += std::to_string(table[1]->getCurFloor());
			log += "-BY-";
			log += std::to_string(elevatorId);
			reverseChart.push_back(std::pair<int, std::string>(passengerId, log));
		}
	}
	extern std::string reversed_input_path;
    std::ofstream file(reversed_input_path);
	std::sort(reverseChart.begin(), reverseChart.end(), cmp);
    for (const auto& t : reverseChart) {
        file << t.second << std::endl;
    }	
    return true;
}

void Parser::convertOriginalFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cout << "Error when opening the file" << std::endl;
		return;
	}
	std::string input;
	std::vector<std::pair<int, std::string>> logs;
	while (std::getline(file, input)) {
		int i = 0;
		while (input[i] != ']') i++;
		i++;
		input = input.substr(i);
		i = 0;
		int id = 0;
		while (input[i] >= '0' && input[i] <= '9') {
			id = id * 10 + input[i] - '0';
			i++;
		}
		logs.push_back(std::pair<int, std::string>(id, input));
	}
	file.close();
	sort(logs.begin(), logs.end(), cmp);
	extern std::string standard_input_path;
	std::ofstream file1(standard_input_path);
	for (const auto& t : logs) {
		file1 << t.second << std::endl;
	}
}
