#include "radarqcp.h"

RadarQcp::RadarQcp(QWidget *parent)
    :QcpWithLegend(parent)
{
    configurePlot();
}

void RadarQcp::configurePlot()
{
//    plot->setInteraction(QCP::iRangeZoom, true);
//    plot->setInteraction(QCP::iRangeDrag, true);
    plot->axisRect()->setupFullAxesBox();

    auto maxDiameter = 2;


    criticalCircle = drawCircle(1, QColor("#FF0000"));
    drawCircle(maxDiameter*maxDiameter, QColor("#FFAAAA"));
    drawCircle(3, QColor("#AAFFAA"));
    drawCircle(1, QColor("#AAAAFF"));

    plot->xAxis->setRange(-maxDiameter, maxDiameter);
    plot->yAxis->setRange(-maxDiameter, maxDiameter);

    configureLines(maxDiameter);
}

void RadarQcp::configureLines(double maxDiameter)
{
    QCPItemLine *hLine = new QCPItemLine(plot);
    hLine->setPen(QPen(Qt::black));
    hLine->start->setCoords(-maxDiameter, 0);
    hLine->end->setCoords(maxDiameter, 0);

    QCPItemLine *vLine = new QCPItemLine(plot);
    vLine->setPen(QPen(Qt::black));
    vLine->start->setCoords(0, -maxDiameter);
    vLine->end->setCoords(0, maxDiameter);

    QCPItemLine *line45 = new QCPItemLine(plot);
    line45->start->setCoords(toPolar(maxDiameter, 45));
    line45->end->setCoords(toPolar(maxDiameter, 180+45));

    QCPItemLine *line135 = new QCPItemLine(plot);
    line135->start->setCoords(toPolar(maxDiameter, 135));
    line135->end->setCoords(toPolar(maxDiameter, 180+135));
}

QPointF RadarQcp::toPolar(double r, double angle)
{
    //TODO rewrite to standart pos
    auto angleDegree = angle*M_PI/180.0;
    return QPointF(r*qCos(angleDegree), r*qSin(angleDegree));
}



QCPItemEllipse* RadarQcp::drawCircle(double radius, QColor color)
{
    auto ellipse = new QCPItemEllipse(plot);
    ellipse->topLeft->setCoords(-radius/2.0, -radius/2.0);
    ellipse->bottomRight->setCoords(radius/2.0, radius/2.0);
    ellipse->setBrush(color);
    return ellipse;
}
