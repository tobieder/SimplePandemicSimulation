#include "AreaChart.h"

#include <QDebug>

AreaChart::AreaChart(QWidget* parent)
	: QChartView(parent)
{
	QChartView::setRenderHint(QPainter::Antialiasing);

	top = new QLineSeries();
	infectedHealthy = new QLineSeries();
	curedHealthy = new QLineSeries();
	healthyImmune = new QLineSeries();
	bottom = new QLineSeries();

	QAreaSeries* sick = new QAreaSeries(bottom, infectedHealthy);
	QAreaSeries* cured = new QAreaSeries(infectedHealthy, curedHealthy);
	QAreaSeries* healthy = new QAreaSeries(curedHealthy, healthyImmune);
	QAreaSeries* immune = new QAreaSeries(healthyImmune, top);

	m_AreaSeries.append(sick);
	m_AreaSeries.append(cured);
	m_AreaSeries.append(healthy);
	m_AreaSeries.append(immune);

	sick->setName("Infected");
	cured->setName("Immune");
	healthy->setName("Healthy");
	immune->setName("Immune");

	QPen pen = QPen(Qt::darkGray);
	pen.setWidth(1);
	healthy->setPen(pen);
	sick->setPen(pen);
	cured->setPen(pen);
	immune->setPen(pen);

	sick->setBrush(COLOR_INFECTED);
	cured->setBrush(COLOR_CURED);
	healthy->setBrush(COLOR_HEALTHY);
	immune->setBrush(COLOR_IMMUNE);

	m_Chart = new QChart();
	m_Chart->addSeries(sick);
	m_Chart->addSeries(cured);
	m_Chart->addSeries(healthy);
	m_Chart->addSeries(immune);

	//m_Chart->setTitle("Area Chart");
	m_Chart->legend()->setVisible(false);

	// ----- Set Axes -----
	QFont openSans("Open Sans");
	openSans.setPointSizeF(8);

	QBrush titleBrush = QBrush(QColor(150, 150, 150));

	m_Chart->createDefaultAxes();
	QValueAxis* m_XAxis = (QValueAxis*)(m_Chart->axes(Qt::Horizontal).first());
	m_XAxis->setTitleText("Time in [s]");
	m_XAxis->setTitleBrush(titleBrush);
	m_XAxis->setTitleFont(openSans);
	m_XAxis->setLabelFormat("%.2f");
	m_XAxis->setLabelsColor(Qt::white);
	m_XAxis->setLabelsFont(openSans);

	QValueAxis* m_YAxis = (QValueAxis*)(m_Chart->axes(Qt::Vertical).first());
	m_YAxis->setTitleText("# Humans");
	m_YAxis->setTitleBrush(titleBrush);
	m_YAxis->setTitleFont(openSans);
	m_YAxis->setLabelFormat("%i");
	m_YAxis->setLabelsColor(Qt::white);
	m_YAxis->setLabelsFont(openSans);
	// ----------------
	
	
	m_Chart->setPlotAreaBackgroundVisible(false);
	m_Chart->setBackgroundVisible(false);

	setChart(m_Chart);

	m_Timer.start();
	timeCounter = 0;
	m_FirstUpdate = true;
}

AreaChart::~AreaChart()
{
}

void AreaChart::AddValues(float _time, int _healthy, int _infected, int _cured, int _immune)
{
	*bottom << QPointF(_time, 0);
	*infectedHealthy << QPointF(_time, _infected);
	*curedHealthy << QPointF(_time, _infected + _cured);
	*healthyImmune << QPointF(_time, _infected + _cured + _healthy);
	*top << QPointF(_time, m_NumHumans);

	m_Chart->axes(Qt::Horizontal).first()->setRange(0, _time);
	m_Chart->axes(Qt::Vertical).first()->setRange(0, m_NumHumans);
}

void AreaChart::SlotUpdateCharts(Statistics* _statistics)
{
	if (m_FirstUpdate)
	{
		m_NumHumans = _statistics->Humans;
		AddValues(timeCounter, _statistics->Healthy, _statistics->Infected, _statistics->Cured, _statistics->Immune);
		m_FirstUpdate = false;
	}
	else
	{
		if (m_Timer.isValid())
		{
			if (m_Timer.hasExpired(1000))
			{
				m_NumHumans = _statistics->Humans;

				timeCounter++;
				m_Timer.restart();
				AddValues(timeCounter, _statistics->Healthy, _statistics->Infected, _statistics->Cured, _statistics->Immune);
			}
		}
	}
}

void AreaChart::SlotResetCharts()
{
	bottom->clear();
	infectedHealthy->clear();
	curedHealthy->clear();
	healthyImmune->clear();
	top->clear();

	timeCounter = 0;
	m_FirstUpdate = true;
}
