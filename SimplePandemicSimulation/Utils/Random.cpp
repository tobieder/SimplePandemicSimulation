#include "Random.h"

#include <algorithm>

Random::Random()
{
	srand(time(NULL));
}

QVector2D Random::RandomQVector2DBetween(QVector2D _min, QVector2D _max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diffX = _max.x() - _min.x();
	float rX = random * diffX;

	random = ((float)rand()) / (float)RAND_MAX;
	float diffY = _max.y() - _min.y();
	float rY = random * diffY;

	return QVector2D(_min.x() + rX, _min.y() + rY);
}

QVector2D Random::AngleToQVector2D(float _angle)
{
	const float angleInRadians = _angle * (M_PI / 180);
	return (QVector2D(cos(_angle), sin(_angle))).normalized();
}

float Random::RandomBetween(float _min, float _max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = _max - _min;
	float r = random * diff;
	return _min + r;
}

std::vector<int> Random::RandomArrayBetween(int _min, int _max)
{
	std::vector<int> vec;

	for (int i = 0; i < (_max - _min); i++)
	{
		vec.push_back(_min + i);
	}

	std::random_shuffle(std::begin(vec), std::end(vec));

	return vec;
}
