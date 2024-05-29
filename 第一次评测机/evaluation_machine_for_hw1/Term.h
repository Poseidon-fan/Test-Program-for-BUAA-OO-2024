#ifndef TERM_H
#define TERM_H
#pragma once
#include <vector>
#include <random>
#include "Functions.h"
class Factor;


class Term
{
private:
	std::vector<std::string>* factors;


public:
	Term();
	void generate();  // ����
	std::string toString();  // ���
	std::string generateExpr();
};

#endif // !TERM_H


