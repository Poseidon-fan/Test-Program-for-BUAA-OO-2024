#ifndef CHECKER_H
#define CHECKER_H

#pragma once
#include "Parser.h"
#include "Person.h"
#include "Elevator.h"
class Checker
{
private:
	Parser* parser;
	std::unordered_map<int, Person*> persons;
	std::string error_path;
	std::vector<std::pair<Reset*, bool>> resets;
	std::unordered_map<int, Elevator*> elevators;

public:
	void parseInput(const std::string& input_path);
	Checker(const std::string& input_path, const std::string& output_path, const std::string& error_path);
	~Checker();
	void writeError(const std::string& error);
	bool checkResets();
	bool finalCheck();
	bool check();
};


#endif // !CHECKER_H

