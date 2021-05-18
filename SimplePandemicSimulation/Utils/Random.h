#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <time.h>

#include <vector>

#include <QVector2D>

class Random
{
public:
	Random();

	static QVector2D RandomQVector2DBetween(QVector2D _min, QVector2D _max);
	static QVector2D AngleToQVector2D(float _angle);

	static float RandomBetween(float _min, float _max);

	static std::vector<int> RandomArrayBetween(int _min, int _max);
};