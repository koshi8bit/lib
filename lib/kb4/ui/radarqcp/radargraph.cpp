#include "radargraph.h"

RadarGraph::RadarGraph(const QString &label, const QString &postfix, QColor color,
                       QCustomPlot *qcp, int precision, bool scientificNotation)
    :AbstractGraph(label, postfix, color, qcp, precision, scientificNotation)
{
    arrow = new QCPItemCurve(qcp);
    arrow->start->setCoords(0, 0);
//    arrow->startDir->setCoords(-1, -1.3);
//    arrow->endDir->setCoords(-5, -0.3);
    setValue(0, 0);
    arrow->setHead(QCPLineEnding::esSpikeArrow);
}

void RadarGraph::setValue(double radius, double angle)
{
    _legendItem->setValue(radius);
    _radius = radius;
    _angle = angle;

    redrawArrow();
}

void RadarGraph::redrawArrow()
{
    arrow->end->setCoords(RadarPlot::toPolar(radius(), angle()));
}

double RadarGraph::angle() const
{
    return _angle;
}

void RadarGraph::setAngle(double angle)
{
    _angle = angle;
}

double RadarGraph::radius() const
{
    return _radius;
}

void RadarGraph::setRadius(double radius)
{
    _legendItem->setValue(radius);
    _radius = radius;
}
