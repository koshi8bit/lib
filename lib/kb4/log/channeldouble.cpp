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
    this->scalingMinValue = minValue;
    this->scalingMaxValue = maxValue;
    this->scalingMinRaw = minRaw;
    this->scalingMaxRaw = maxRaw;

    setToScaledFunc([this](double raw)
    {
        return (raw - this->scalingMinRaw) / (this->scalingMaxRaw - this->scalingMinRaw) *
                (this->scalingMaxValue - this->scalingMinValue) + this->scalingMinValue;
    });

    setToRawFunc([this](double scaled)
    {
        return (scaled - this->scalingMinValue) / (this->scalingMaxValue - this->scalingMinValue) *
                (this->scalingMaxRaw - this->scalingMinRaw) + this->scalingMinRaw;
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

double ChannelDouble::valueBuffered()
{
    if (bufferSize() < 2)
        return value();

    auto result = 0.0;
    foreach(auto element, buffer)
    {
        result += element;
    }
    result /= buffer.count();
    return result;
}

int ChannelDouble::bufferSize() const
{
    return _bufferSize;
}

void ChannelDouble::setBufferSize(int bufferSize)
{
    _bufferSize = bufferSize;
}

void ChannelDouble::setRange(double min, double max)
{
    rangeMin = min;
    rangeMax = max;
    setRange(true);
}

void ChannelDouble::setRange(bool emitSignal)
{
    rangeEmitSignal = emitSignal;
    if (emitSignal)
    {
        auto current = inRange();

        emit inRangeChanged(current);
        emit inRangeChangedInverted(!current);

        inRangePrev = current;
    }
}

bool ChannelDouble::inRange()
{
    return EasyLiving::isBetween(value(), rangeMin, rangeMax);
}

void ChannelDouble::configure()
{
    connect(this, &Channel::valueChanged, [this]() { emit valueChangedDouble(value()); } );
    setScientificNotation(false);
    setPrecision(3);
}

void ChannelDouble::valueSetChild()
{
    if (rangeEmitSignal)
    {
        auto current = inRange();

        if (current != inRangePrev)
        {
            emit inRangeChanged(current);
            emit inRangeChangedInverted(!current);
        }

        inRangePrev = current;
    }

    if (bufferSize() >= 2)
    {
        buffer.push_back(value());
        if (buffer.size() > _bufferSize)
            buffer.pop_front();
    }

    if (toRawFunc != nullptr) { _rawValue = toRawFunc(value()); }

    if (realTimeGraph() != nullptr) { realTimeGraph()->addData(RealTimePlot::currentDateTime(), this->value()); }
}
