/**
* AreaChart - Tobias Eder
*
* Displaying the Pandemic data in an area chart using QtCharts.
*
* 
*/

#pragma once

#include <QWidget>
#include <QElapsedTimer>
#include <QMap>
#include <QPainter>

#include <QtCharts/QChartView>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>

#include <QtCharts/QValueAxis>

#include <vector>

#include "Utils/Statistics.h"
#include "Utils/Colors.h"

QT_CHARTS_USE_NAMESPACE

class AreaChart
	: public QChartView
{
	Q_OBJECT

public:
	AreaChart(QWidget* parent);
	~AreaChart();

	void AddValues(float _time, int _healthy, int _infected, int _cured, int _immune);

private:
	QVector<QAreaSeries*> m_AreaSeries;
	QChart* m_Chart;

	QPainter m_Painter;

	QLineSeries* bottom;
	QLineSeries* infectedHealthy;
	QLineSeries* curedHealthy;
	QLineSeries* healthyImmune;
	QLineSeries* top;

	QElapsedTimer m_Timer;
	int timeCounter;

	bool m_HasBeenInitialized;
	int m_NumberOfDataSets;
	float m_SumOfValues;
	float m_MaxSumOfValues;

	int m_NumHumans;
	bool m_FirstUpdate;

public slots:
	void SlotUpdateCharts(Statistics* _stats);
	void SlotResetCharts();
};

