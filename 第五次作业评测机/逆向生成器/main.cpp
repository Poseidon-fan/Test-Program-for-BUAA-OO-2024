#define _CRT_SECURE_NO_WARNINGS
#include "Parser.h"
int minFloor = 1;
int maxFloor = 11;
int eleNum = 6;
int capacity = 6;
std::string origin_input_path, origin_output_path, standard_input_path, reversed_input_path, error_path;

int main(int argc, char* argv[])
{
	origin_input_path = argv[1];
	origin_output_path = argv[2];
	standard_input_path = argv[3];
	reversed_input_path = argv[4];
	error_path = argv[5];
	auto x = freopen(argv[5], "w", stdout);
	Parser parser({1, 2, 3, 4, 4, 6});
	parser.parseSequences(origin_output_path);
	bool res = parser.checkProcessValidity();
	Parser::convertOriginalFile(origin_input_path);
	// system("pause");
	return res == true ? 0 : 1;
}