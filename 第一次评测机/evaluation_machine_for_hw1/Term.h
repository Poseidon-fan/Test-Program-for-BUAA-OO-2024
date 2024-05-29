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
	void generate();  // Éú³É
	std::string toString();  // Êä³ö
	std::string generateExpr();
};

#endif // !TERM_H


