#ifndef CHANNELT_H
#define CHANNELT_H

#include <QStringList>

#include "channel.h"

template <typename T>
class ChannelT : public Channel
{
public:
    ChannelT(QString name, QString postfix, QStringList *path, QObject *parent = nullptr)
        :Channel(name, postfix, path, parent)
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
        //emit valueChanged(newValue);
        emit valueChanged();
    }

private:
    T _value;

protected:

//signals:
//    void valueChanged(T newValue);

};


#endif // CHANNEL_H
