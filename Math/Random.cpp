#include "Random.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>

void Srand() { srand(static_cast<unsigned int>(time(NULL))); }

int GetRand(const int start, const int end)
{
	int adjust = 1;
	if (start > end) { adjust = -1; }
	int div = end - start;
	if (div > 0) div++;
	if (div < 0) div--;
	if (div == 0) return end;

	return adjust * ((rand() % div) + start);
}

float GetRandF(const float start, const float end, const int place)
{
	const int p = static_cast<int>(powf(10, static_cast<float>(place)));
	const int s = static_cast<int>(start * p);
	const int e = static_cast<int>(end * p);
	float result = static_cast<float>(GetRand(s, e)) / p;
	return result;
}
