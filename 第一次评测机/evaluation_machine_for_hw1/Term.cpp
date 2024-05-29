#include "Term.h"




Term::Term()
{
	factors = new std::vector<std::string>;
}

void Term::generate()
{
	factors->clear();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution <>dis(1, 10);
	int size = dis(gen);

	for (int i = 0; i < size; i++) {
		factors->push_back(Factor::getFactor());
	}
}

std::string Term::toString()
{
	std::string res = "";
	res += (*factors)[0];
	for (unsigned int i = 1; i < factors->size(); i++) {
		res += "*";
		res += (*factors)[i];
	}
	return res;
}

std::string Term::generateExpr()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution <>dis(1, 10);
	int size = dis(gen);
	std::string res = "";
	Term* term = new Term();
	term->generate();
	res += term->toString();
	for (int i = 1; i < size; i++) {
		res += getRandomBool() ? "-" : "+";
		term->generate();
		res += term->toString();
	}
	return res;
}
