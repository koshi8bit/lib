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

void ChannelDouble::setScaling(double minValue, double maxValue, double minRaw, double maxRaw)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
    this->minRaw = minRaw;
    this->maxRaw = maxRaw;

    setToScaledFunc([this](double raw)
    {
        return (raw - this->minRaw) / (this->maxRaw - this->minRaw) *
                (this->maxValue - this->minValue) + this->minValue;
    });

    setToRawFunc([this](double scaled)
    {
        return (scaled - this->minValue) / (this->maxValue - this->minValue) *
                (this->maxRaw - this->minRaw) + this->minRaw;
    });
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

double ChannelDouble::valueBuffered() const
{
    if (bufferSize == 0)
        return 0;

    auto result = 0.0;
    foreach(auto element, buffer)
    {
        result += element;
    }
    result /= buffer.count();
    return result;
}

void ChannelDouble::configure()
{
    connect(this, &Channel::valueChanged, [this]() { emit valueChangedDouble(value()); } );
    setScientificNotation(false);
    setPrecision(3);
}

void ChannelDouble::valueSetChild()
{
    if (bufferSize > 0)
    {
        buffer.push_back(value());
        if (buffer.size() > bufferSize)
            buffer.pop_front();
    }

    if (toRawFunc != nullptr) { _rawValue = toRawFunc(value()); }

    if (realTimeGraph() != nullptr) { realTimeGraph()->addData(RealTimePlot::currentDateTime(), this->value()); }
}
