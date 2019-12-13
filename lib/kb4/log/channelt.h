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

    void configureSharedVariable(bool connectWrite=false)
    {
        sharedVariable = new NetVar<T>(logName());
        qDebug() << "sharedVariable" << logName() << "created";
        if (connectWrite)
        {
            connect(sharedVariable, &NetVarBase::valueChanged, this, &ChannelT::sharedVariableUpdated);
        }
    }

public slots:
    void setValue(T newValue)
    {
        _setValue(newValue);

        if (sharedVariable)
        {
            sharedVariable->setValue(newValue);
            sharedVariable->send();
        }
    }



private:
    T _value;
    NetVar<T> *sharedVariable = nullptr;

    void _setValue(T newValue)
    {
        _value = newValue;
        valueChangedChild();

        //qDebug() << "valueChanged" << logName() << newValue;
        emit valueChanged();
//      emit valueChanged777(_value);
    }

    void sharedVariableUpdated()
    {
        _setValue(sharedVariable->value());
    }

protected:
    virtual void valueChangedChild()
    {

    }

//signals:
//    void valueChanged777(T newValue);

};


#endif // CHANNEL_H
