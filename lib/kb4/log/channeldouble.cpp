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


void ChannelDouble::setRawValue(double newRawValue)
{
    if (fromRawScaleFunc == nullptr)
    {
        emit errorOcurred(EL_FORMAT_ERR(QString("fromRawScaleFunc == nullptr at channel '%1'").arg(logName())));
        return;
    }
    setValue(fromRawScaleFunc(newRawValue));
}

void ChannelDouble::setFromRawScaleFunc(double (*f)(double))
{
    fromRawScaleFunc = f;
}

void ChannelDouble::setToRawScaleFunc(double (*f)(double))
{
    toRawScaleFunc = f;
}

double ChannelDouble::rawValue()
{
    return _rawValue;
}

void ChannelDouble::valueChangedChild()
{
    if (toRawScaleFunc == nullptr)
        return;

    _rawValue = toRawScaleFunc(value());
}

void ChannelDouble::addDataToGraph()
{
    graph->addData(RTPlotWithLegend::now(), value());
}
