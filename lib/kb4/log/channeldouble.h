#ifndef CHANNELDOUBLE_H
#define CHANNELDOUBLE_H

#include "channelrealtimegraph.h"

class ChannelDouble : public ChannelRealTimeGraph<double>
{
    Q_OBJECT
public:
    ChannelDouble(QString name, QString postfix, QObject *parent = nullptr);
    ChannelDouble(QString name, QString postfix, QStringList &path, QObject *parent = nullptr);
    ChannelDouble(QString sharedVariableName, QObject *parent = nullptr);
    ~ChannelDouble() override;

    void setScaling(double scalingMinValue, double scalingMaxValue, double scalingMinRaw, double scalingMaxRaw);

    void setToScaledFunc(std::function<double(double)> f);
    void setRawValue(double newValue);

    void setToRawFunc(std::function<double(double)> f);
    double rawValue();


    double valueBuffered();

    int bufferSize() const;
    void setBufferSize(int bufferSize);

    void setRange(double min, double max);
    void setRange(bool emitSignal);
    bool inRange();

private:

    //double (*toScaledFunc)(double) = nullptr;
    std::function<double(double)> toScaledFunc = nullptr;

    double _rawValue;
    //double (*toRawFunc)(double) = nullptr;
    std::function<double(double)> toRawFunc = nullptr;
    double scalingMinValue=0, scalingMaxValue=0, scalingMinRaw=0, scalingMaxRaw=0;
    double rangeMin=0, rangeMax=0;
    bool rangeEmitSignal = false, inRangePrev = false;

    //QQueue<double> buffer;
    QLinkedList<double> buffer;
    int _bufferSize = 1;

    void configure();
signals:
    //TODO: template fuck
    //void valueChangedDouble(double newValue);
    void inRangeChanged(bool inRange);

protected:
    void valueSetChild() override;
private slots:
};

#endif // CHANNELDOUBLE_H
