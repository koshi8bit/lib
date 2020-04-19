#include "channeldouble.h"

ChannelDouble::ChannelDouble(QString name, QString postfix, QObject *parent)
    :ChannelT<double>(name, postfix, parent)
{
    configure();
}

ChannelDouble::ChannelDouble(QString name, QString postfix, QStringList &path, QObject *parent)
    :ChannelT<double>(name, postfix, path, parent)
{
    configure();
}

ChannelDouble::ChannelDouble(QString sharedVariableName, QObject *parent)
    :ChannelT<double>(sharedVariableName, parent)
{
    configure();
}

void ChannelDouble::addGraphToPlot(RealTimePlot *plot, bool visible)
{
    _graphRealTimePlot = plot->addGraph(plotName(), postfix(), precision(), scientificNotation());
    _graphRealTimePlot->setVisible(visible);
    if (color().isValid())
        _graphRealTimePlot->setColor(color());
}

//AbstractGraph *ChannelDouble::addGraphToPlot(AbstractPlot *plot, bool visible)
//{
//    _abstractGraph = plot->addGraph(plotName(), postfix(), precision(), scientificNotation());
//    _abstractGraph->setVisible(visible);
//    if (color().isValid())
//        _abstractGraph->setColor(color());

//    return _abstractGraph;
//}


bool ChannelDouble::scientificNotation()
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

int ChannelDouble::precision() const
{
    return _precision;
}

void ChannelDouble::setPrecision(int precision)
{
    _precision = precision;
}

void ChannelDouble::configure()
{
    connect(this, &Channel::valueChanged, [this]() { emit valueChangedDouble(value()); } );
    setScientificNotation(false);
    setPrecision(3);
}

void ChannelDouble::valueChangedChild()
{
    if (toRawFunc != nullptr) { _rawValue = toRawFunc(value()); }

    if (_graphRealTimePlot != nullptr) { _graphRealTimePlot->addData(RealTimePlot::currentDateTime(), value()); }

    //if (_abstractGraph != nullptr) { _abstractGraph->addData(RealTimeQCP::currentDateTime(), value()); }
}

void ChannelDouble::_valueChanged()
{
    //TODO: template fuck
    //emit valueChangedDouble(value());
}

