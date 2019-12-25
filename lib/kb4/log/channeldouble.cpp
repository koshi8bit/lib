#include "channeldouble.h"



//ChannelDouble::ChannelDouble(QString sharedVariableName, QString postfix, bool connectWrite, QObject *parent)
//    :ChannelT<double>(sharedVariableName, postfix, connectWrite, parent)
//{

//}

//ChannelDouble::ChannelDouble(QString name, QString postfix, QStringList &prefix, QObject *parent)
//    :ChannelT<double>(name, postfix, &prefix, parent)
//{

//}

//ChannelDouble::ChannelDouble(QString name, QString postfix, QStringList *prefix, QObject *parent)
//    :ChannelT<double>(name, postfix, prefix, parent)
//{
//    //TODO: template imperfection. See _valueChanged
//    //connect(this, &Channel::valueChanged, this, &ChannelDouble::_valueChanged);
//}


ChannelDouble::ChannelDouble(QString name, QString postfix, QObject *parent)
    :ChannelT<double>(name, postfix, parent)
{

}

ChannelDouble::ChannelDouble(QString name, QString postfix, QStringList &path, QObject *parent)
    :ChannelT<double>(name, postfix, path, parent)
{

}

ChannelDouble::ChannelDouble(QString sharedVariableName, bool connectWrite, QObject *parent)
    :ChannelT<double>(sharedVariableName, connectWrite, parent)
{

}

ChannelDouble::ChannelDouble(QString sharedVariableName, QString postfix, bool connectWrite, QObject *parent)
    :ChannelT<double>(sharedVariableName, postfix, connectWrite, parent)
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

void ChannelDouble::setToScaledFunc(std::function<double(double)> f)
{
    toScaledFunc = f;
}

void ChannelDouble::setToRawFunc(std::function<double(double)> f)
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

void ChannelDouble::_valueChanged()
{
    //TODO: template fuck
    //emit valueChangedDouble(value());
}

void ChannelDouble::addDataToGraph()
{
    graph->addData(RealTimeQCP::currentDateTime(), value());
}
