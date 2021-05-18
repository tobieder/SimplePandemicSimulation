/**
* PandemicWidget - Tobias Eder
* 
* The main Widget which displays the simulation and controls the Parameters.
* 
* The visible part of this widget is responsible for rendering and controlling the 
* visual part of the simulation, mainly by using the Pandemic class.
* This class also represents the control hub for all the user parameters, which can be
* set during runtime and affect the simulation.
*/

#pragma once

#include <time.h>

#include <QWidget>
#include <QPainter>
#include <QElapsedTimer>

#include "Pandemic/Pandemic.h"
#include "Utils/Colors.h"

class PandemicWidget
	: public QWidget
{
	Q_OBJECT

public:
	PandemicWidget(QWidget* _parent);
	~PandemicWidget();

private:

	QWidget* m_Parent;
	QPainter m_Painter;

	Pandemic* m_Pandemic;

	QElapsedTimer m_UpdateTimer;

	bool m_SimulationRunning;

	int m_InitHumans;
	double m_InitSicknessRate;

	int m_HumanSpeed;

	double m_InitImmuneRate;

	double m_socialDistancingAdoption;

	Disease m_Disease;

private:
	void paintEvent(QPaintEvent* event);

	void resizeEvent(QResizeEvent* event);

public slots:
	void SlotNumberHumans(int _value);
	void SlotInitSicknessRate(int _value);

	void SlotHumanSpeed(int _value);

	void SlotInitImmuneRate(int _value);

	void SlotContagiousPeriod(double _value);
	void SlotContagiousPeriodVariance(double _value);
	void SlotPropabilityOfInfection(double _value);

	void SlotUpdateSocialDistancingAdoption(double _value);

	void SlotStartRestartSimulation();
	void SlotStopSimulation();

signals:
	void SignalUpdateStatistics(Statistics* _stats);
	void SignalResetCharts();

	void SignalUpdateAbsoluteInfected(int _infected);
	void SignalUpdateInfectedRange(int _min, int _max);

	void SignalUpdateHumanSpeedLabel(int _speed);

	void SignalUpdateAbsoluteImmune(int _immune);
	void SignalUpdateImmuneRange(int _min, int _max);

	void SignalUpdateHealthyCount(int _healthy);
	void SignalUpdateInfectedCount(int _infected);
	void SignalUpdateCuredCount(int _cured);
	void SignalUpdateImmuneCount(int _immune);

	void SignalSetHealthyColor(QColor _color);
	void SignalSetInfectedColor(QColor _color);
	void SignalSetCuredColor(QColor _color);
	void SignalSetImmuneColor(QColor _color);
};

