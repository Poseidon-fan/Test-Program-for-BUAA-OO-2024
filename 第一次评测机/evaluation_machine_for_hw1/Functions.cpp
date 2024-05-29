#include "Functions.h"


long getRandomLong() {
	// 使用当前的时间作为随机数生成器的种子
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<long> dis(std::numeric_limits<long>::min(), std::numeric_limits<long>::max());

	// 生成一个随机长整数  
	return dis(gen);
}

bool getRandomBool() {
	// 创建一个随机数引擎  
	std::random_device rd;
	std::mt19937 gen(rd());

	// 创建一个分布对象，用于生成0或1  
	std::bernoulli_distribution dis(0.5);

	// 生成随机数并转换为bool  
	bool random_bool = dis(gen);

	return random_bool;
}
