#ifndef FACTOR_H
#define FACTOR_H
#pragma once
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include "Functions.h"
class Term;


class Factor
{
protected:
	std::string content;

public:
	std::string getContent();  // 获取内容
	virtual void generate() = 0;  // 生成
	static std::string getFactor();
	
};

class NumberFactor : Factor
{
public:

	void generate() override;  // 生成一个带符号整数，存储到content属性中
	using Factor::getContent;

};

class VariableFactor : Factor
{
public:
	void generate() override;  // 生成一个幂函数
	using Factor::getContent;
};

class ExprFactor : Factor
{
public:
	void generate() override;  // 生成一个表达式因子
	using Factor::getContent;
};


#endif // !FACTOR_H

