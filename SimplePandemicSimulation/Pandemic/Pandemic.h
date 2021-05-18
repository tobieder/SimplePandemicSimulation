/**
* Pandemic - Tobias Eder
*
* Handling all Human and Disease Data of the Pandemic Simulation.
* 
* The Pandemic class is defined by the number of humans, the initial sickness rate, the intial immune rate
* and the disease that drives the pandemic.
*/

#pragma once

#include <time.h>

#include <QVector>

#include "Disease.h"
#include "../Human/Human.h"
#include "../Utils/Statistics.h"
#include "../Utils/Random.h"

class Pandemic
{
public:
	Pandemic(QWidget* _parent, QVector2D _min, QVector2D _max, int _initNumHumans, double _initSicknessRate, double _initImmuneRate, Disease _disease);
	~Pandemic();

	void Update(float _deltaTime, QPainter& _painter);
	void SetMinMax(QVector2D _min, QVector2D _max);

	void SetHumanSpeed(float _speed);

	void SetDisease(Disease _disease) { m_Disease = _disease; }

	void SetSocialDistancing(double _adoption);

	Statistics& GetStatistics() { return m_Statistics; }

	void SetSimulationRunning(bool _isRunning);

private:
	Disease m_Disease;
	QVector<Human*> m_Humans;

	Statistics m_Statistics;

	bool m_SimulationRunning;
};

