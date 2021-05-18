/**
* Human - Tobias Eder
*
* Data representation of a Human used to simulate a Pandemic.
* 
* A Human gets defined by its size, speed/velocity and the position as well as its current HealthState.
* During each Update a Human executes three steps:
*	1. Move according to its randomly assigend velocity.
*	2. Update its Disease.
*	3. Call the HumanVisualizer to draw its updated position and color.
*/

#pragma once

#include <QVector2D>
#include <QTime>
#include <QElapsedTimer>

#include "HumanVisualizer.h"

#include "HumanVisualizer.h"
#include "../Utils/Random.h"
#include "../Utils/Statistics.h"
#include "../Utils/Colors.h"

enum class HealthState { HEALTHY, INFECTED, CURED, IMMUNE };

class Human
{
public:
	Human(QWidget* _parent, Statistics& _statistics, QVector2D _min, QVector2D _max);
	Human(QWidget* _parent, Statistics& _statistics, QVector2D _position, QVector2D _velocity, QVector2D _min, QVector2D _max, HealthState _healthState, float _timeToHeal = 0.0f);
	~Human();

	void Update(float _deltaTime, QPainter& _painter);

	float GetRadius() { return m_Size / 2.0f; }

	void SetSpeed(float _speed);

	void SetSimulationRunning(bool _isRunning) { m_SimulationRunning = _isRunning; }

	void SetSocialDistancing(bool _socialDistancing) { m_SocialDistancing = _socialDistancing; }

	HealthState getHealthState() { return m_HealthState; }
	void SetHealthState(HealthState _healthState);

	void SetMinMax(QVector2D _min, QVector2D _max) { m_Min = _min; m_Max = _max; }
	QVector2D GetMin() { return m_Min; }
	QVector2D GetMax() { return m_Max; }

	QVector2D getPosition() { return m_Position; }

	void Billiard();
	void Billiard(QVector2D _objectPosition);

	void Infect(float _timeToHeal);
	void Immunize();

	QVector2D GetVelocity() { return m_Velocity; }

private:

	void Heal();

private:
	float m_Speed = 25.0;
	float m_Size = 7.5f;

	float m_TimeToHeal;

	bool m_SocialDistancing = false;

	bool m_SimulationRunning;

	HealthState m_HealthState;

	Statistics& m_Statistics;

	QVector2D m_Position;
	QVector2D m_Velocity;

	QVector2D m_Min, m_Max;

	QElapsedTimer m_SickTime;

	HumanVisualizer* m_HumanVisualizer;
};

