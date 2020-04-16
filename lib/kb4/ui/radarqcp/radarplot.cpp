#include "radarplot.h"

RadarPlot::RadarPlot(QWidget *parent)
    :AbstractPlot(parent)
{
    configurePlot();
}

void RadarPlot::configurePlot()
{
//    plot->setInteraction(QCP::iRangeZoom, true);
//    plot->setInteraction(QCP::iRangeDrag, true);
    _plot->axisRect()->setupFullAxesBox();

    auto maxDiameter = 2;


    criticalCircle = drawCircle(1, QColor("#FF0000"));
    drawCircle(maxDiameter*maxDiameter, QColor("#FFAAAA"));
    drawCircle(3, QColor("#AAFFAA"));
    drawCircle(1, QColor("#AAAAFF"));

    _plot->xAxis->setRange(-maxDiameter, maxDiameter);
    _plot->yAxis->setRange(-maxDiameter, maxDiameter);

    configureLines(maxDiameter);
}

void RadarPlot::configureLines(double maxDiameter)
{
    QCPItemLine *hLine = new QCPItemLine(_plot);
    hLine->setPen(QPen(Qt::black));
    hLine->start->setCoords(-maxDiameter, 0);
    hLine->end->setCoords(maxDiameter, 0);

    QCPItemLine *vLine = new QCPItemLine(_plot);
    vLine->setPen(QPen(Qt::black));
    vLine->start->setCoords(0, -maxDiameter);
    vLine->end->setCoords(0, maxDiameter);

    QCPItemLine *line45 = new QCPItemLine(_plot);
    line45->start->setCoords(toPolar(maxDiameter, 45));
    line45->end->setCoords(toPolar(maxDiameter, 180+45));

    QCPItemLine *line135 = new QCPItemLine(_plot);
    line135->start->setCoords(toPolar(maxDiameter, 135));
    line135->end->setCoords(toPolar(maxDiameter, 180+135));
}

QPointF RadarPlot::toPolar(double r, double angle)
{
    //TODO rewrite to standart pos
    auto angleDegree = angle*M_PI/180.0;
    return QPointF(r*qCos(angleDegree), r*qSin(angleDegree));
}

RadarGraph *RadarPlot::addGraph(const QString &label, const QString &postfix, int precision, bool scientificNotation)
{
    auto graph = new RadarGraph(label,
                                   postfix,
                                   colorSetter.getColor(),
                                   qcp(),
                                   precision,
                                   scientificNotation);
    AbstractPlot::addGraph(graph);
    return graph;
}



QCPItemEllipse* RadarPlot::drawCircle(double radius, QColor color)
{
    auto ellipse = new QCPItemEllipse(_plot);
    ellipse->topLeft->setCoords(-radius/2.0, -radius/2.0);
    ellipse->bottomRight->setCoords(radius/2.0, radius/2.0);
    ellipse->setBrush(color);
    return ellipse;
}
