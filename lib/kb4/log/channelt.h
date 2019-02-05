#ifndef CHANNELT_H
#define CHANNELT_H

#include <QStringList>

#include "channel.h"

template <typename T>
class ChannelT : public Channel
{
public:
    ChannelT(QString plotText, QStringList logName, QObject *parent = nullptr)
        :Channel(plotText, logName, parent)
    {
        _value = T();
    }

    T value()
    {
        return _value;
    }

public slots:
    void setValue(T newValue)
    {
        _value = newValue;
        emit valueChanged();
    }

private:
    T _value;

protected:

};


#endif // CHANNEL_H
