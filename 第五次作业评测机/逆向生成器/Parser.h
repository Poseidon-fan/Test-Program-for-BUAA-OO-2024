#ifndef PARSER_H
#define PARSER_H
#pragma once
#include <vector>
#include <unordered_map>
#include "Request.h"
#include "Arrive.h"
#include "Open.h"
#include "Close.h"
#include "In.h"
#include "Out.h"
#include <string>
#include <iostream>
#include <fstream>

class Parser
{
private:
	std::unordered_map<int, std::vector<Request*>> elevators;  // 电梯：ID -> 输出序列
	
	// 添加一个请求序列到电梯中
	void addRequest(const std::string &input);

public:
	Parser(std::vector<int> eleIds);
	~Parser();
	void parseSequences(const std::string &filePath);
	bool checkProcessValidity();
	static void convertOriginalFile(const std::string& filePath);
	

};

#endif // !PARSER_H

