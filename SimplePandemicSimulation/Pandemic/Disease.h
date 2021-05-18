#pragma once

struct Disease
{
	Disease(float _contagiousPeriod, float _contagiousPeriodVariance, float _propabilityOfInfection)
	{
		contagiousPeriod = _contagiousPeriod;
		contagiousPeriodVariance = _contagiousPeriodVariance;

		propabilityOfInfection = _propabilityOfInfection;
	}

	float contagiousPeriod;
	float contagiousPeriodVariance;

	float propabilityOfInfection;
};