#include "Parser.h"


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


double parseTime(const std::string& str) {
	size_t openPos = str.find('[');
	size_t closePos = str.find(']');

	// 提取中括号内的子字符串  
	std::string numberStr = str.substr(openPos + 1, closePos - openPos - 1);

	// 使用istringstream解析浮点数  
	std::istringstream iss(numberStr);
	double value;
	if (!(iss >> value)) {
		throw std::invalid_argument("Invalid format: cannot parse float from bracketed string.");
	}

	return value;
}


Log* parseOneLog(const std::string& log) {
	// 解析时间戳
	double time = parseTime(log);
	int i = 1;
	while (log[i] != ']') i++; i++;
	std::string tmp = log.substr(i);

	std::vector<std::string> tokens = split_string(tmp, '-');
	if (tokens[0] == "ARRIVE") {
		int curFloor = std::stoi(tokens[1]);
		int elevatorId = std::stoi(tokens[2]);
		Arrive* l = new Arrive(time, curFloor, elevatorId);
		return l;
	}
	else if (tokens[0] == "OPEN") {
		int curFloor = std::stoi(tokens[1]);
		int elevatorId = std::stoi(tokens[2]);
		Open* l = new Open(time, curFloor, elevatorId);
		return l;
	}
	else if (tokens[0] == "CLOSE") {
		int curFloor = std::stoi(tokens[1]);
		int elevatorId = std::stoi(tokens[2]);
		Close* l = new Close(time, curFloor, elevatorId);
		return l;
	}
	else if (tokens[0] == "IN") {
		int passengerId = std::stoi(tokens[1]);
		int curFloor = std::stoi(tokens[2]);
		int elevatorId = std::stoi(tokens[3]);
		In* l = new In(time, curFloor, elevatorId, passengerId);
		return l;
	}
	else if (tokens[0] == "OUT") {
		int passengerId = std::stoi(tokens[1]);
		int curFloor = std::stoi(tokens[2]);
		int elevatorId = std::stoi(tokens[3]);
		Out* l = new Out(time, curFloor, elevatorId, passengerId);
		return l;
	}
	else if (tokens[0] == "RESET_ACCEPT") {
		int elevatorId = std::stoi(tokens[1]);
		int capacity = std::stoi(tokens[2]);
		double speed = std::stod(tokens[3]);
		Reset* l = new Reset(time, Type::RESET_ACCEPT, elevatorId, capacity, speed);
		return l;
	}
	else if (tokens[0] == "RESET_BEGIN") {
		int elevatorId = std::stoi(tokens[1]);
		Reset* l = new Reset(time, Type::RESET_BEGIN, elevatorId);
		return l;
	}
	else if (tokens[0] == "RESET_END") {
		int elevatorId = std::stoi(tokens[1]);
		Reset* l = new Reset(time, Type::RESET_END, elevatorId);
		return l;
	}
	else if (tokens[0] == "RECEIVE") {
		int passengerId = std::stoi(tokens[1]);
		int elevatorId = std::stoi(tokens[2]);
		Receive* l = new Receive(time, elevatorId, passengerId);
		return l;
	}
	else {
		std::cout << "Error when parsing log" << std::endl;
	}
	return nullptr;
}


Parser::Parser(const std::string& output_path)
{
	this->logStream = new std::vector<Log*>;
	parseOutput(output_path);
	//printLogs();
	//parseEachElevatorLogs();
}

Parser::~Parser()
{
	for (Log* log : *logStream) {
		delete log;
	}
	delete logStream;
}

void Parser::parseOutput(const std::string& output_path)
{
	std::ifstream file(output_path);
	std::string log;  // 文件中的每一行原始输出
	while (std::getline(file, log)) {
		logStream->push_back(parseOneLog(log));
	}
	file.close();
}

void Parser::parseEachElevatorLogs()
{
	for (Log* log : *logStream) {
		elevatorsLogStream[log->getElevatorId()].push_back(log);
	}
}

void Parser::printLogs()
{
	for (Log* log : *logStream) {
		std::cout << log->toString() << std::endl;
	}
}

void Parser::printEachElevatorLogs()
{
	for (const auto& pair : elevatorsLogStream) {
		std::cout << pair.first << std::endl;
		for (Log* log : pair.second) {
			std::cout << log->toString() << std::endl;
		}
		std::cout << std::endl;
	}
}

std::vector<Log*>* Parser::getLogStream()
{
	return logStream;
}
