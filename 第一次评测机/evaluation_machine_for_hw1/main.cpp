#include <iostream>

#include "Term.h"

int main() 
{
	Term* t = new Term();
	std::cout << t->generateExpr();

	
	return 0;
}