#include "channellogdouble.h"

ChannelLogDouble::ChannelLogDouble(QString name, QString postfix, QStringList *path, QObject *parent)
    :ChannelLogT<double>(name, postfix, path, parent)
{

}

//to constructor?
void ChannelLogDouble::setGraph(Graph *graph)
{
    this->graph = graph;
    connect(this, &Channel::valueChanged, this, &ChannelLogDouble::addDataToGraph);
}

void ChannelLogDouble::addDataToGraph()
{
    graph->addData(RTPlotWithLegend::now(), value());
}
