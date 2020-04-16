#include "radargraph.h"

RadarGraph::RadarGraph(const QString &label, const QString &postfix,
                       QColor color, QCustomPlot *qcp, int precision,
                       bool scientificNotation, int width)
    :AbstractGraph(label, postfix, color, qcp, precision, scientificNotation)
{
    arrow = new QCPItemLine(qcp);
    arrow->start->setCoords(0, 0);
    setValue(0, 0);

    arrow->setHead(QCPLineEnding::esSpikeArrow);

    _setColor(color);
    setWidth(width);
}

void RadarGraph::_setColor(QColor color)
{
    QPen pen;
    pen.setColor(color);
    pen.setWidth(width());
    arrow->setPen(pen);
}

QPointF RadarGraph::toPolar(double r, double angle)
{
    //TODO copy from radarplot DRY
    auto angleDegree = angle*M_PI/180.0;
    return QPointF(r*qCos(angleDegree), r*qSin(angleDegree));
}


void RadarGraph::setValue(double radius, double angle)
{
    _legendItem->setValue(radius);
    _radius = radius;
    _angle = angle;

    redrawArrow();
}

int RadarGraph::width() const
{
    return _width;
}

void RadarGraph::setWidth(int width)
{
    _width = width;
}

void RadarGraph::redrawArrow()
{
    //    _legendItem->setValue(QString("%1 (%2)")
    //                          .arg(EasyLiving::formatDouble(radius(), 1))
//                          .arg(EasyLiving::formatDouble(angle(), 0)));

    _legendItem->setValue(radius());
    arrow->end->setCoords(toPolar(radius(), angle()));
}

void RadarGraph::abstractSetVisible(bool newValue)
{
    arrow->setVisible(newValue);
}

void RadarGraph::abstractSetColor(QColor color)
{
    _setColor(color);
}

double RadarGraph::angle() const
{
    return _angle;
}

void RadarGraph::setAngle(double angle)
{
    _angle = angle;
    redrawArrow();
}

double RadarGraph::radius() const
{
    return _radius;
}

void RadarGraph::setRadius(double radius)
{
    _radius = radius;
    redrawArrow();
}
