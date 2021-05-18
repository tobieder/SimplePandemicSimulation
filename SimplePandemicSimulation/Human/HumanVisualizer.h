#pragma once

#include <QWidget>
#include <Qvector2D>
#include <QPainter>
#include <QPen>
#include <QBrush>

class HumanVisualizer
	: public QWidget
{
	Q_OBJECT

public:
    HumanVisualizer(QWidget* _parent, QVector2D _min, QVector2D _max, float _size);
    ~HumanVisualizer();

    void Draw(QPainter& _aPainter, QPointF _position);

    void SetColor(QColor _color);

    void SetMinMax(QVector2D _min, QVector2D _max);

private:
    float m_Size;

    QBrush m_Brush;
    QPen m_Pen;

    QColor m_Color;

    QRectF m_PointShape;

    QVector2D m_Min;
    QVector2D m_Max;
};

