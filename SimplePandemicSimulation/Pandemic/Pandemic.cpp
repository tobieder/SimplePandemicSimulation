#include "Pandemic.h"

#include <QDebug>

Pandemic::Pandemic(QWidget* _parent, QVector2D _min, QVector2D _max, int _initNumHumans, double _initSicknessRate, double _initImmuneRate, Disease _disease)
	:m_Disease(_disease)
{
	srand(time(NULL));

	m_Humans = QVector<Human*>();

	for (int i = 0; i < _initNumHumans; i++)
	{
		m_Humans.append(new Human(_parent, m_Statistics, _min, _max));
	}

	m_Statistics.Humans = _initNumHumans;

	std::vector<int> randomArray = Random::RandomArrayBetween(0, _initNumHumans);

	int initSickHumans = (int)(_initNumHumans * _initSicknessRate);
	int initImmuneHumans = (int)(_initNumHumans * _initImmuneRate);

	for (int i = 0; i < initSickHumans; i++)
	{
		float actualTimeToCure = m_Disease.contagiousPeriod + Random::RandomBetween(-m_Disease.contagiousPeriodVariance, m_Disease.contagiousPeriodVariance);
		m_Humans[randomArray[i]]->Infect(actualTimeToCure);
	}

	for (int i = initSickHumans; i < initSickHumans + initImmuneHumans; i++)
	{
		m_Humans[randomArray[i]]->Immunize();
	}

	m_SimulationRunning = true;
}

Pandemic::~Pandemic()
{
	m_Humans.clear();
}

void Pandemic::Update(float _deltaTime, QPainter& _painter)
{
	// ------ Update humans -----
	QVectorIterator<Human*> itHumansUpdate(m_Humans);
	while(itHumansUpdate.hasNext())
	{
		Human* currHuman = itHumansUpdate.next();

		currHuman->Update(_deltaTime, _painter);
	}

	// ------ Update Infection -----
	QVectorIterator<Human*> itHumansDisease(m_Humans);
	while (itHumansDisease.hasNext())
	{
		Human* currHuman = itHumansDisease.next();

		QVectorIterator<Human*> itOtherHuman(m_Humans);
		while (itOtherHuman.hasNext())
		{
			Human* currOtherHuman = itOtherHuman.next();
			float distance = currHuman->getPosition().distanceToPoint(currOtherHuman->getPosition());

			if (distance <= (currHuman->GetRadius() + currOtherHuman->GetRadius()))
			{
				if (currHuman != currOtherHuman)
				{
					if (currHuman->getHealthState() == HealthState::INFECTED)
					{
						if (currOtherHuman->getHealthState() == HealthState::HEALTHY)
						{
							if (((float)(rand() % 100) / 100.0f) < m_Disease.propabilityOfInfection)
							{
								float actualTimeToCure = m_Disease.contagiousPeriod + Random::RandomBetween(-m_Disease.contagiousPeriodVariance, m_Disease.contagiousPeriodVariance);
								currOtherHuman->Infect(actualTimeToCure);
							}
						}
					}

					currHuman->Billiard(currOtherHuman->getPosition());
				}
			}
		}
	}
}

void Pandemic::SetMinMax(QVector2D _min, QVector2D _max)
{
	QVectorIterator<Human*> itHumans(m_Humans);
	while (itHumans.hasNext())
	{
		itHumans.next()->SetMinMax(_min, _max);
	}
}

void Pandemic::SetHumanSpeed(float _speed)
{
	QVectorIterator<Human*> itHumans(m_Humans);
	while (itHumans.hasNext())
	{
		itHumans.next()->SetSpeed(_speed);
	}
}

void Pandemic::SetSocialDistancing(double _adoption)
{
	int absoluteAdoption = (int)(m_Humans.size() * _adoption);

	int i = 0;
	for (; i < absoluteAdoption; i++)
	{
		m_Humans[i]->SetSocialDistancing(true);
	}
	for (; i < m_Humans.size(); i++)
	{
		m_Humans[i]->SetSocialDistancing(false);
	}
}

void Pandemic::SetSimulationRunning(bool _isRunning)
{
	m_SimulationRunning = _isRunning;

	QVectorIterator<Human*> itHumansUpdate(m_Humans);
	while (itHumansUpdate.hasNext())
	{
		itHumansUpdate.next()->SetSimulationRunning(_isRunning);
	}
}
