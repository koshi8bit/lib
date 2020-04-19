#include "radartemperature4plot.h"

RadarTemperature4Plot::RadarTemperature4Plot(QWidget *parent)
    :RadarPlot(parent)
{
//    plot->setInteraction(QCP::iRangeZoom, true);
//    plot->setInteraction(QCP::iRangeDrag, true);
//    _qcp->axisRect()->setupFullAxesBox();

    auto maxDiameter = 2;


    criticalCircle = drawCircle(1, QColor("#FF0000"));
    drawCircle(maxDiameter*maxDiameter, QColor("#FFAAAA"));
    drawCircle(3, QColor("#AAFFAA"));
    drawCircle(2, QColor("#AAFFAA"));
    drawCircle(1, QColor("#AAAAFF"));

    _qcp->xAxis->setRange(-maxDiameter, maxDiameter);
    _qcp->yAxis->setRange(-maxDiameter, maxDiameter);

    configureLines(maxDiameter);
}

RadarTemperature4Graph *RadarTemperature4Plot::addGraph(const QString &label,
    ChannelDouble *up, ChannelDouble *right, ChannelDouble *down,
    ChannelDouble *left, int precision, int lineWidth)
{
    auto graph = new RadarTemperature4Graph(label,
                                colorSetter.getColor(),
                                qcp(),
                                up, right, down, left,
                                precision,
                                false,
                                lineWidth);
    AbstractPlot::addGraph(graph);
    return graph;
}

QCPItemEllipse *RadarTemperature4Plot::drawCircle(double radius, QColor color)
{
    auto ellipse = new QCPItemEllipse(_qcp);
    ellipse->topLeft->setCoords(-radius/2.0, -radius/2.0);
    ellipse->bottomRight->setCoords(radius/2.0, radius/2.0);
    ellipse->setBrush(color);
    return ellipse;
}

void RadarTemperature4Plot::configureLines(double maxDiameter)
{
    QCPItemLine *hLine = new QCPItemLine(_qcp);
    hLine->start->setCoords(-maxDiameter, 0);
    hLine->end->setCoords(maxDiameter, 0);

    QCPItemLine *vLine = new QCPItemLine(_qcp);
    vLine->start->setCoords(0, -maxDiameter);
    vLine->end->setCoords(0, maxDiameter);

    QCPItemLine *line45 = new QCPItemLine(_qcp);
    line45->start->setCoords(toPolar(maxDiameter, 45));
    line45->end->setCoords(toPolar(maxDiameter, 180+45));

    QCPItemLine *line135 = new QCPItemLine(_qcp);
    line135->start->setCoords(toPolar(maxDiameter, 135));
    line135->end->setCoords(toPolar(maxDiameter, 180+135));
}
