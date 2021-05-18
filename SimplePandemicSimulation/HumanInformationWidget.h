#pragma once

#include <QWidget>
#include <QPainter>

#include "Human/HumanVisualizer.h"

class HumanInformationWidget
	: public QWidget
{
	Q_OBJECT

public:
	HumanInformationWidget(QWidget* _parent);
	~HumanInformationWidget();

private:
	QPainter m_Painter;
	float m_Size = 7.5f;

	QColor m_Color;

	QBrush m_Brush;
	QPen m_Pen;

	QRectF m_PointShape;

private:
	void paintEvent(QPaintEvent* event);

	void resizeEvent(QResizeEvent* event);

public slots:
	void SlotSetColor(QColor _color);
};

