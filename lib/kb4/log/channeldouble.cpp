#include "channeldouble.h"

ChannelDouble::ChannelDouble(QString name, QStringList *path, QObject *parent)
    :ChannelT<double>(name, path, parent)
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
