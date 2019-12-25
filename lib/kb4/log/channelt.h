#ifndef CHANNELT_H
#define CHANNELT_H

#include <QStringList>

#include "channel.h"
#include <lib/kb4/shared-variable/tcp/netvars.h>

template <typename T>
class ChannelT : public Channel
{
public:
    ChannelT(QString name, QString postfix, QObject *parent = nullptr)
        :Channel(name, postfix, parent)
    {
        _value = T();
    }

    ChannelT(QString name, QString postfix, QStringList &path, QObject *parent = nullptr)
        :Channel(name, postfix, path, parent)
    {
        _value = T();
    }

    ChannelT(QString sharedVariableName, QObject *parent = nullptr)
        :Channel(getName(sharedVariableName), "", parent)
    {
        setLogName(getName(sharedVariableName));
        _value = T();

        //configure and get postfix
        //postfix=

        configureSharedVariable(true);
    }

    T value()
    {
        return _value;
    }

    void setSharedVariableEnableWriteFromNet(bool enable)
    {
        if (enable)
        {
            connect(sharedVariable, &NetVarBase::valueChanged, this, &ChannelT::sharedVariableUpdated);
        }
        else
        {
            disconnect(sharedVariable, &NetVarBase::valueChanged, this, &ChannelT::sharedVariableUpdated);
        }

    }

    void configureSharedVariable(bool enableWriteFromNet = false)
    {
        sharedVariable = new NetVar<T>(logName());
#ifdef SV_SHOW_DEBUG
        qDebug() << "sharedVariable" << logName() << "created";
#endif
        setSharedVariableEnableWriteFromNet(enableWriteFromNet);
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
    static QString getName(QString sharedVariableName)
    {
        return sharedVariableName.split("/").last();
    }

    static QStringList* getPath(QString sharedVariableName)
    {
        QStringList* result = new QStringList(sharedVariableName.split(Channel::seporator));
        result->removeLast();
        qDebug() << result;
        return result;
    }

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
