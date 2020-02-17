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
        setLogName(sharedVariableName);
        _value = T();

        //configure and get postfix
        //setPostfix=???

        //child
        //setPrecision(??);
        //setScientificNotation(??);


        configureSharedVariable(true);
    }

    T value()
    {
        return _value;
    }

    void setSharedVariableEnableReadFromNet(bool enable)
    {
        if (enable)
        {
            connect(sharedVariable, &NetVarBase::valueChanged,
                    this, &ChannelT::sharedVariableUpdated, Qt::QueuedConnection);
        }
        else
        {
            disconnect(sharedVariable, &NetVarBase::valueChanged,
                       this, &ChannelT::sharedVariableUpdated);
        }

    }

    void configureSharedVariable(bool enableWriteFromNet = false)
    {
        sharedVariable = new NetVar<T>(logName());
        connect(sharedVariable, &NetVarBase::valueChanged,
                this, &ChannelT<T>::updateSharedVariable, Qt::QueuedConnection);
#ifdef K8B_LIB_CHANNELS_SHOW_SV_CREATED
        qDebug() << "sharedVariable" << logName() << "created";
#endif
        setSharedVariableEnableReadFromNet(enableWriteFromNet);
    }


public slots:
    void setValue(T newValue)
    {
        _setValue(newValue);

//        if (sharedVariable)
//        {
//            sharedVariable->setValue(newValue);
//            sharedVariable->send();
//        }
    }

private slots:
    void updateSharedVariable()
    {
        sharedVariable->setValue(value());
        sharedVariable->send();
    }




private:
    static QString getName(QString sharedVariableName)
    {
        return sharedVariableName.split("/").last();
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
