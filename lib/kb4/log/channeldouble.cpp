#include "channeldouble.h"

ChannelDouble::ChannelDouble(QString name, QString postfix, QObject *parent)
    :ChannelRealTimeGraph<double>(name, postfix, parent)
{
    configure();
}

ChannelDouble::ChannelDouble(QString name, QString postfix, QStringList &path, QObject *parent)
    :ChannelRealTimeGraph<double>(name, postfix, path, parent)
{
    configure();
}

ChannelDouble::ChannelDouble(QString sharedVariableName, QObject *parent)
    :ChannelRealTimeGraph<double>(sharedVariableName, parent)
{
    configure();
}

ChannelDouble::~ChannelDouble()
{
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

void ChannelDouble::configure()
{
    connect(this, &Channel::valueChanged, [this]() { emit valueChangedDouble(value()); } );
    setScientificNotation(false);
    setPrecision(3);
}

void ChannelDouble::valueChangedChild()
{
    if (toRawFunc != nullptr) { _rawValue = toRawFunc(value()); }

    if (realTimeGraph() != nullptr) { realTimeGraph()->addData(RealTimePlot::currentDateTime(), this->value()); }
}
