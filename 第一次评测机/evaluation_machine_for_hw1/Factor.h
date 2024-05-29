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
	std::string getContent();  // ��ȡ����
	virtual void generate() = 0;  // ����
	static std::string getFactor();
	
};

class NumberFactor : Factor
{
public:

	void generate() override;  // ����һ���������������洢��content������
	using Factor::getContent;

};

class VariableFactor : Factor
{
public:
	void generate() override;  // ����һ���ݺ���
	using Factor::getContent;
};

class ExprFactor : Factor
{
public:
	void generate() override;  // ����һ�����ʽ����
	using Factor::getContent;
};


#endif // !FACTOR_H

