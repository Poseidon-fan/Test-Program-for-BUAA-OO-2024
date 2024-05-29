#include "Checker.h"

int main(int argc, char* argv[])
{
	Checker checker(argv[1], argv[2], argv[3]);
	if (checker.check()) printf("AC!\n");
	else printf("WA!");
	//int res = checker.check() ? 0 : 1;
	system("pause");
	return 0;
}