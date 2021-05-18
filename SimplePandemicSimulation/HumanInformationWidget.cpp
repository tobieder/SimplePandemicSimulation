#include "HumanInformationWidget.h"

HumanInformationWidget::HumanInformationWidget(QWidget* _parent)
{
	m_Color = QColor(255, 0, 255, 255);

	m_PointShape = QRectF(-0.5f * m_Size, -0.5f * m_Size, m_Size, m_Size);

	m_Brush.setStyle(Qt::BrushStyle::SolidPattern);
	m_Brush.setColor(m_Color);

	//QWidget::update();
}

HumanInformationWidget::~HumanInformationWidget()
{
}

void HumanInformationWidget::paintEvent(QPaintEvent* event)
{
	m_Painter.begin(this);

	m_Painter.setRenderHints(QPainter::Antialiasing);

	m_Painter.setBrush(m_Brush);

	m_Painter.save();
	m_Painter.translate((rect().bottomRight() - m_PointShape.toRect().bottomRight()) / 2);
	m_Painter.drawEllipse(m_PointShape);
	m_Painter.restore();

	m_Painter.end();

	//QWidget::update();
}

void HumanInformationWidget::resizeEvent(QResizeEvent* event)
{
	QWidget::update();
}

void HumanInformationWidget::SlotSetColor(QColor _color)
{
	m_Color = _color;
	m_Brush.setColor(m_Color);

	QWidget::update();
}
