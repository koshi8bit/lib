#include "channeldouble.h"

ChannelDouble::ChannelDouble(QString name, QString postfix, QStringList *path, QObject *parent)
    :ChannelT<double>(name, postfix, path, parent)
{

}

void ChannelDouble::setGraph(Graph *graph)
{
    this->graph = graph;
    connect(this, &Channel::valueChanged, this, &ChannelDouble::addDataToGraph);
}

bool ChannelDouble::isScientificNotation()
{
    return _scientificNotation;
}

void ChannelDouble::setScientificNotation(bool newValue)
{
    _scientificNotation = newValue;
}

double ChannelDouble::raw()
{
    return _raw;
}

void ChannelDouble::setRawValue(double newRawValue)
{
    if (rawScaleFunc == nullptr)
    {
        emit errorOcurred("rawScaleFunc == nullptr");
        return;
    }
    setValue(rawScaleFunc(newRawValue));
}

void ChannelDouble::setRawScaleFunc(double (*f)(double))
{
    rawScaleFunc = f;
}

void ChannelDouble::addDataToGraph()
{
    graph->addData(RTPlotWithLegend::now(), value());
}
