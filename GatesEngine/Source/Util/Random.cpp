#include "..\..\Header\Util\Random.h"

std::mt19937_64 GE::RandomMaker::rnd = std::mt19937_64();

int GE::RandomMaker::GetInt(int minValue, int maxValue)
{
	std::uniform_int_distribution<int> range(minValue, maxValue);
	return range(rnd);
}

float GE::RandomMaker::GetFloat(float minValue, float maxValue)
{
	std::uniform_real_distribution<float> range(minValue, maxValue);
	return range(rnd);
}
