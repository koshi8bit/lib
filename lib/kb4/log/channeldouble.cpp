#include "channeldouble.h"

ChannelDouble::ChannelDouble(QString name, QString postfix, QStringList *prefix, QObject *parent)
    :ChannelT<double>(name, postfix, prefix, parent)
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
    if (toScaledFunc == nullptr)
    {
        _errorOccurred(EL_FORMAT_ERR(QString("fromRawScaleFunc == nullptr at channel '%1'").arg(logName())));
        return;
    }
    setValue(toScaledFunc(newRawValue));
}

void ChannelDouble::setToScaledFunc(double (*f)(double))
{
    toScaledFunc = f;
}

void ChannelDouble::setToRawFunc(double (*f)(double))
{
    toRawFunc = f;
}

double ChannelDouble::rawValue()
{
    //FIXME DRY
    if (toRawFunc == nullptr)
    {
        _errorOccurred(EL_FORMAT_ERR(QString("toRawFunc == nullptr at channel '%1'").arg(logName())));
        return 0;
    }

    return _rawValue;
}

void ChannelDouble::valueChangedChild()
{
    if (toRawFunc != nullptr)
    {
        _rawValue = toRawFunc(value());
    }
}

void ChannelDouble::addDataToGraph()
{
    graph->addData(RTPlotWithLegend::now(), value());
}
