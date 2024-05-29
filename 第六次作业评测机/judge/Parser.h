#ifndef PARSER_H
#define PARSER_H

#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Log.h"
#include "Arrive.h"
#include "Open.h"
#include "Close.h"
#include "In.h"
#include "Out.h"
#include "Reset.h"
#include "Receive.h"

class Parser
{
private:
	std::vector<Log*>* logStream;
	std::unordered_map<int, std::vector<Log*>> elevatorsLogStream;

public:
	Parser(const std::string& output_path);
	~Parser();
	void parseOutput(const std::string& output_path);
	void parseEachElevatorLogs();
	void printLogs();
	void printEachElevatorLogs();

	std::vector<Log*>* getLogStream();
};

#endif // !PARSER_H


