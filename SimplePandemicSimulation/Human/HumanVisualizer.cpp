#include "HumanVisualizer.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <QDebug>


HumanVisualizer::HumanVisualizer(QWidget* parent, QVector2D _min, QVector2D _max, float _size)
	: QWidget(parent), m_Size(_size)
{
	m_Color = QColor(255, 0, 255, 255);

	m_PointShape = QRectF(-0.5f * m_Size, -0.5f * m_Size, m_Size, m_Size);

	m_Brush.setStyle(Qt::BrushStyle::SolidPattern);
	m_Brush.setColor(m_Color);
}

HumanVisualizer::~HumanVisualizer()
{
}

void HumanVisualizer::Draw(QPainter& _aPainter, QPointF _position)
{
	_aPainter.setRenderHints(QPainter::Antialiasing);

	_aPainter.setBrush(m_Brush);

	_aPainter.save();
	_aPainter.translate(_position);
	_aPainter.drawEllipse(m_PointShape);
	_aPainter.restore();
}

void HumanVisualizer::SetColor(QColor _color)
{
	m_Color = _color;
	m_Brush.setColor(_color);
}

void HumanVisualizer::SetMinMax(QVector2D _min, QVector2D _max)
{
	m_Min = _min;
	m_Max = _max;
}