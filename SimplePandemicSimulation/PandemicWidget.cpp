#include "PandemicWidget.h"

#include <QDebug>

PandemicWidget::PandemicWidget(QWidget* _parent)
	: QWidget(_parent), m_Disease(10.0f, 1.0f, 1.0f)
{
	m_Parent = _parent;
	m_Pandemic = nullptr;

	m_SimulationRunning = false;

	// Setting the default values to the same values specified in the .ui-File.
	m_InitHumans = 300;
	m_InitSicknessRate = 0.1;
	m_HumanSpeed = 25;
	m_InitImmuneRate = 0;
	m_socialDistancingAdoption = 0.0;

	this->SignalUpdateImmuneRange(0, 100 - (int)(m_InitSicknessRate * 100.0f));
	this->SignalUpdateInfectedRange(0, 100 - (int)(m_InitImmuneRate * 100.0f));

	srand(time(NULL));

	m_UpdateTimer.start();
}

PandemicWidget::~PandemicWidget()
{
}

void PandemicWidget::paintEvent(QPaintEvent* event)
{
	// Calculating the FrameTime to allow for constant movement speed with different FPS.
	float deltaTime = ((float)(m_UpdateTimer.restart()) / (float)(1000));


	this->SignalSetHealthyColor(COLOR_HEALTHY);
	this->SignalSetInfectedColor(COLOR_INFECTED);
	this->SignalSetCuredColor(COLOR_CURED);
	this->SignalSetImmuneColor(COLOR_IMMUNE);

	m_Painter.begin(this);

	// Set the background color of the widget.
	m_Painter.fillRect(rect(), QColor(100, 100, 100, 255));

	if (m_Pandemic != nullptr)
	{
		if(!m_SimulationRunning)
		{
			// Stop simulation
			m_Pandemic->SetSimulationRunning(false);

			this->SignalUpdateHealthyCount(m_Pandemic->GetStatistics().Healthy);
			this->SignalUpdateInfectedCount(m_Pandemic->GetStatistics().Infected);
			this->SignalUpdateCuredCount(m_Pandemic->GetStatistics().Cured);
			this->SignalUpdateImmuneCount(m_Pandemic->GetStatistics().Immune);
		}
		else
		{
			if (m_Pandemic->GetStatistics().Infected <= 0)
			{
				m_SimulationRunning = false;
			}

			this->SignalUpdateStatistics(&m_Pandemic->GetStatistics());

			this->SignalUpdateHealthyCount(m_Pandemic->GetStatistics().Healthy);
			this->SignalUpdateInfectedCount(m_Pandemic->GetStatistics().Infected);
			this->SignalUpdateCuredCount(m_Pandemic->GetStatistics().Cured);
			this->SignalUpdateImmuneCount(m_Pandemic->GetStatistics().Immune);
		}

		// Update the simulation.
		m_Pandemic->Update(deltaTime, m_Painter);
	}

	m_Painter.end();

	QWidget::update();
}

void PandemicWidget::resizeEvent(QResizeEvent* event)
{
	if (m_Pandemic != nullptr)
	{
		QVector2D min(QWidget::x() + 4, QWidget::y() + 4);
		QVector2D max(QWidget::x() + QWidget::geometry().width(), QWidget::y() + QWidget::height());

		m_Pandemic->SetMinMax(min, max);
	}
}

void PandemicWidget::SlotNumberHumans(int _value)
{
	m_InitHumans = _value;

	this->SignalUpdateAbsoluteInfected((int)(m_InitHumans * m_InitSicknessRate));
}

void PandemicWidget::SlotInitSicknessRate(int _value)
{
	m_InitSicknessRate = ((double)_value) / ((double)100.0);

	this->SignalUpdateAbsoluteInfected((int)(m_InitHumans * m_InitSicknessRate));
	this->SignalUpdateImmuneRange(0, 100 - (int)(m_InitSicknessRate * 100));
}

void PandemicWidget::SlotHumanSpeed(int _value)
{
	m_HumanSpeed = _value;

	this->SignalUpdateHumanSpeedLabel(m_HumanSpeed);

	if (m_Pandemic != nullptr)
	{
		m_Pandemic->SetHumanSpeed(m_HumanSpeed);
	}
}

void PandemicWidget::SlotInitImmuneRate(int _value)
{
	m_InitImmuneRate = ((double)_value) / ((double)100.0);

	this->SignalUpdateAbsoluteImmune((int)(m_InitHumans * m_InitImmuneRate));
	this->SignalUpdateInfectedRange(0, 100 - (int)(m_InitImmuneRate * 100));
}

void PandemicWidget::SlotContagiousPeriod(double _value)
{
	m_Disease.contagiousPeriod = _value;

	if (m_Pandemic != nullptr)
	{
		m_Pandemic->SetDisease(m_Disease);
	}
}

void PandemicWidget::SlotContagiousPeriodVariance(double _value)
{
	m_Disease.contagiousPeriodVariance = _value;

	if (m_Pandemic != nullptr)
	{
		m_Pandemic->SetDisease(m_Disease);
	}
}

void PandemicWidget::SlotPropabilityOfInfection(double _value)
{
	m_Disease.propabilityOfInfection = _value;

	if (m_Pandemic != nullptr)
	{
		m_Pandemic->SetDisease(m_Disease);
	}
}

void PandemicWidget::SlotUpdateSocialDistancingAdoption(double _value)
{
	m_socialDistancingAdoption = _value;

	if (m_Pandemic != nullptr)
	{
		m_Pandemic->SetSocialDistancing(_value);
	}
}

void PandemicWidget::SlotStartRestartSimulation()
{
	// Calculating the min and max Positions for Humans.
	QVector2D min(QWidget::x() + 4, QWidget::y() + 4);
	QVector2D max(QWidget::x() + QWidget::geometry().width() - 7, QWidget::y() + QWidget::height() - 7);

	m_Pandemic = new Pandemic(m_Parent, min, max, m_InitHumans, m_InitSicknessRate, m_InitImmuneRate, m_Disease);

	m_Pandemic->SetSocialDistancing(m_socialDistancingAdoption);
	m_Pandemic->SetHumanSpeed(m_HumanSpeed);

	this->SignalResetCharts();
	this->SignalUpdateStatistics(&m_Pandemic->GetStatistics());

	this->SignalUpdateHealthyCount(m_Pandemic->GetStatistics().Healthy);
	this->SignalUpdateInfectedCount(m_Pandemic->GetStatistics().Infected);
	this->SignalUpdateCuredCount(m_Pandemic->GetStatistics().Cured);
	this->SignalUpdateImmuneCount(m_Pandemic->GetStatistics().Immune);

	m_SimulationRunning = true;
}

void PandemicWidget::SlotStopSimulation()
{
	m_SimulationRunning = false;

	if (m_Pandemic != nullptr)
	{
		m_Pandemic->SetSimulationRunning(false);

		this->SignalUpdateHealthyCount(m_Pandemic->GetStatistics().Healthy);
		this->SignalUpdateInfectedCount(m_Pandemic->GetStatistics().Infected);
		this->SignalUpdateCuredCount(m_Pandemic->GetStatistics().Cured);
		this->SignalUpdateImmuneCount(m_Pandemic->GetStatistics().Immune);
	}
}
