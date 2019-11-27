#ifndef CHANNELT_H
#define CHANNELT_H

#include <QStringList>

#include "channel.h"
#include <lib/kb4/shared-variable/tcp/netvars.h>

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
        valueChangedChild();

        if (sharedVariable)
            sharedVariable->setValue(_value);

        emit valueChanged();
//      emit valueChanged777(_value);
    }

    void configureSharedVariable()
    {
        sharedVariable = new NetVar<T>(logName);
    }

private:
    T _value;
    NetVar<T> *sharedVariable = nullptr;

protected:
    virtual void valueChangedChild()
    {

    }

//signals:
//    void valueChanged777(T newValue);

};


#endif // CHANNEL_H
