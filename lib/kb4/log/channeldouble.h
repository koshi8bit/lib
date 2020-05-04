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

    void setToScaledFunc(std::function<double(double)> f);
    void setRawValue(double newValue);

    void setToRawFunc(std::function<double(double)> f);
    double rawValue();

private:

    //double (*toScaledFunc)(double) = nullptr;
    std::function<double(double)> toScaledFunc = nullptr;

    double _rawValue;
    //double (*toRawFunc)(double) = nullptr;
    std::function<double(double)> toRawFunc = nullptr;

    void configure();
signals:
    //TODO: template fuck
    //void valueChangedDouble(double newValue);

protected:
    void valueChangedChild() override;
private slots:
};

#endif // CHANNELDOUBLE_H
