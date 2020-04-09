#include "radargraph.h"

RadarGraph::RadarGraph(const QString &label, const QString &postfix, QColor color,
                       RadarPlot *plot, int precision, bool scientificNotation)
    :AbstractGraph(label, postfix, color, precision, scientificNotation, plot)
{
    this->plot = plot;

    arrow = new QCPItemCurve(plot->qcp());
    arrow->start->setCoords(0, 0);
//    arrow->startDir->setCoords(-1, -1.3);
//    arrow->endDir->setCoords(-5, -0.3);
    setValue(0, 0);
    arrow->setHead(QCPLineEnding::esSpikeArrow);
}

void RadarGraph::setValue(double r, double angle)
{
    _graphLegendItem->setValue(r);
    arrow->end->setCoords(r, angle);

}
