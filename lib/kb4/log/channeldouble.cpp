#include "channeldouble.h"

ChannelDouble::ChannelDouble(QString displayName, QStringList logName, QObject *parent)
    :ChannelT<double>(displayName, logName, parent)
{

}

void ChannelDouble::setGraph(Graph *graph)
{
    this->graph = graph;
    connect(this, &Channel::valueChanged, this, &ChannelDouble::addDataToGraph);
}

void ChannelDouble::addDataToGraph()
{
    graph->addData(RTPlotWithLegend::now(), value());
}
