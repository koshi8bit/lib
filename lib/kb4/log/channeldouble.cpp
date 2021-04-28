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

double ChannelDouble::calcAvg(AvgFunc func, double *error)
{
    if (bufferSize() < 2)
        return value();

    if (func == AvgFunc::ArithmeticMean)
        return calcArithmeticMean();

    if (func == AvgFunc::StandardDeviation)
    {
        return calcStandardDeviation(error);
    }

}

double ChannelDouble::calcArithmeticMean()
{
    auto result = 0.0;
    foreach(auto element, buffer)
    {
        result += element;
    }
    result /= buffer.count();
    return result;
}

double ChannelDouble::calcStandardDeviation(double *error)
{

    double avarage_mu = calcArithmeticMean();

    if (error == nullptr)
        return avarage_mu;

    double summ=0;
    foreach(auto element, buffer)
    {
        summ += qPow(element - avarage_mu, 2);
    }
    auto sigma_pow_2 = summ/(buffer.count() - 1); // -1 is not bug, watch here https://ru.wikipedia.org/wiki/%D0%A1%D1%80%D0%B5%D0%B4%D0%BD%D0%B5%D0%BA%D0%B2%D0%B0%D0%B4%D1%80%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B5_%D0%BE%D1%82%D0%BA%D0%BB%D0%BE%D0%BD%D0%B5%D0%BD%D0%B8%D0%B5#%D0%9F%D1%80%D0%B8%D0%BC%D0%B5%D1%80_%D0%B2%D1%8B%D1%87%D0%B8%D1%81%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F_%D1%81%D1%82%D0%B0%D0%BD%D0%B4%D0%B0%D1%80%D1%82%D0%BD%D0%BE%D0%B3%D0%BE_%D0%BE%D1%82%D0%BA%D0%BB%D0%BE%D0%BD%D0%B5%D0%BD%D0%B8%D1%8F_%D0%BE%D1%86%D0%B5%D0%BD%D0%BE%D0%BA_%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D0%BA%D0%BE%D0%B2
    *error = qSqrt(sigma_pow_2);

    return avarage_mu;
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
    setRangeEnable(true);
}

void ChannelDouble::setRangeEnable(bool rangeEnable)
{
    this->rangeEnable = rangeEnable;
    if (rangeEnable)
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
    if (rangeEnable)
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
