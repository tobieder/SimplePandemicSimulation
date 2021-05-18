#include "Human.h"

#include <QDebug>

Human::Human(QWidget* _parent, Statistics& _statistics, QVector2D _min, QVector2D _max)
	: m_Statistics(_statistics), m_Min(_min), m_Max(_max)
{
	m_Position = Random::RandomQVector2DBetween(m_Min, m_Max);
	m_Velocity = Random::AngleToQVector2D(rand() % 360) * m_Speed;

	m_SickTime.invalidate();

	m_HumanVisualizer = new HumanVisualizer(_parent, _min, _max, m_Size);
	SetHealthState(HealthState::HEALTHY);

	m_SimulationRunning = true;
}

Human::Human(QWidget* _parent, Statistics& _statistics, QVector2D _position, QVector2D _velocity, QVector2D _min, QVector2D _max, HealthState _healthState, float _timeToHeal)
	: m_Statistics(_statistics), m_Position(_position), m_Velocity(_velocity), m_Min(_min), m_Max(_max)
{
	m_SickTime.invalidate();

	if (_healthState == HealthState::INFECTED)
	{
		Infect(_timeToHeal);
	}
	else
	{
		SetHealthState(_healthState);
	}

	m_HumanVisualizer = new HumanVisualizer(_parent, _min, _max, m_Size);
}

Human::~Human()
{
}

void Human::Update(float _deltaTime, QPainter& _painter)
{
	if (m_SimulationRunning)
	{
		// ----- MOVE -----
		if (!m_SocialDistancing)
		{
			m_Position += (m_Velocity * _deltaTime);
			if (m_Position.x() >= m_Max.x() || m_Position.x() <= m_Min.x() || m_Position.y() >= m_Max.y() || m_Position.y() <= m_Min.y())
			{
				Billiard();
			}
		}
		// ----- MOVE -----

		// ----- SICKNESS -----
		if (m_HealthState == HealthState::INFECTED)
		{
			if (m_SickTime.isValid())
			{
				if (m_SickTime.hasExpired(m_TimeToHeal))
				{
					SetHealthState(HealthState::CURED);
					m_SickTime.invalidate();
				}
			}
		}
		// ----- SICKNESS -----
	}

	// ----- DRAW -----
	m_HumanVisualizer->Draw(_painter, m_Position.toPointF());
	// ----- DRAW -----
}

// Set a new speed and update the velocity.
void Human::SetSpeed(float _speed)
{ 
	m_Speed = _speed;
	
	m_Velocity = m_Velocity.normalized() * m_Speed;
}

// Updating the HealthState, setting the according color and updating the statistics.
void Human::SetHealthState(HealthState _healthState)
{
	m_HealthState = _healthState;

	switch (m_HealthState)
	{
	case HealthState::HEALTHY: 
		m_HumanVisualizer->SetColor(COLOR_HEALTHY);
		m_Statistics.Healthy++;
		break;
	case HealthState::INFECTED:
		m_HumanVisualizer->SetColor(COLOR_INFECTED);
		m_Statistics.Infect();
		break;
	case HealthState::CURED:
		m_HumanVisualizer->SetColor(COLOR_CURED);
		m_Statistics.Heal();
		break;
	case HealthState::IMMUNE:
		m_HumanVisualizer->SetColor(COLOR_IMMUNE);
		m_Statistics.Immunize();
		break;
	}
}

// Bounce of the border of the widget by behaving like a billiard ball.
void Human::Billiard()
{
	if (m_Position.x() >= m_Max.x() || m_Position.x() <= m_Min.x())
	{
		m_Velocity.setX(-m_Velocity.x());
	}
	else if (m_Position.y() >= m_Max.y() || m_Position.y() <= m_Min.y())
	{
		m_Velocity.setY(-m_Velocity.y());
	}
}

// Bounce of another Human (shaped like a circle) by using its position.
void Human::Billiard(QVector2D _objectPosition)
{
	QVector2D difference = (_objectPosition - m_Position).normalized() * m_Speed;

	m_Velocity.setX(-difference.x());
	m_Velocity.setY(-difference.y());
}

void Human::Infect(float _timeToHeal)
{
	SetHealthState(HealthState::INFECTED);

	m_TimeToHeal = (_timeToHeal * 1000);
	m_SickTime.start();

}

void Human::Immunize()
{
	SetHealthState(HealthState::IMMUNE);
}

void Human::Heal()
{
	SetHealthState(HealthState::CURED);

	m_SickTime.invalidate();
}
