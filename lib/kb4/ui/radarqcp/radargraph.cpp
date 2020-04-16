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

void RadarGraph::setValue(double r, double angle)
{
    _legendItem->setValue(r);
    arrow->end->setCoords(r, angle);

}
