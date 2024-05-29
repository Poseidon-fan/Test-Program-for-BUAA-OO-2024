#include "Functions.h"


long getRandomLong() {
	// ʹ�õ�ǰ��ʱ����Ϊ�����������������
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<long> dis(std::numeric_limits<long>::min(), std::numeric_limits<long>::max());

	// ����һ�����������  
	return dis(gen);
}

bool getRandomBool() {
	// ����һ�����������  
	std::random_device rd;
	std::mt19937 gen(rd());

	// ����һ���ֲ�������������0��1  
	std::bernoulli_distribution dis(0.5);

	// �����������ת��Ϊbool  
	bool random_bool = dis(gen);

	return random_bool;
}
