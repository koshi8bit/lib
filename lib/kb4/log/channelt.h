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

    ~ChannelT()
    {
        if (sharedVariable)
            sharedVariable->deleteLater();
    }

    virtual T value()
    {
        return _value;
    }

    void setSharedVariableEnableReadFromNet(bool enable)
    {
        if (enable)
        {
            connect(sharedVariable, &NetVarBase::valueChanged,
                    this, &ChannelT::sharedVariableUpdated);
        }
        else
        {
            disconnect(sharedVariable, &NetVarBase::valueChanged,
                       this, &ChannelT::sharedVariableUpdated);
        }

    }

    QString configureSharedVariable(bool enableWriteFromNet = false)
    {
        sharedVariable = new NetVar<T>(logName());

#ifdef K8B_LIB_CHANNELS_SHOW_SV_CREATED
        qDebug() << "sharedVariable" << logName() << "created";
#endif
        setSharedVariableEnableReadFromNet(enableWriteFromNet);
        return logName();
    }

    void askSharedVariable()
    {
        sharedVariable->ask();
    }

//    void setMultithreading(bool enable)
//    {
//        _multithreading = enable;
//        if (enable)
//        {
//            connect(this, &Channel::valueChanged,
//                    this, &ChannelT<T>::updateSharedVariable, Qt::QueuedConnection);
//        }
//        else
//        {
//            disconnect(this, &Channel::valueChanged,
//                    this, &ChannelT<T>::updateSharedVariable);
//        }
//    }


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

private slots:
    void updateSharedVariable()
    {
        sharedVariable->setValue(value());
        sharedVariable->send();
    }




protected:

private:
    T _value;
    bool _multithreading = false;

    NetVar<T> *sharedVariable = nullptr;

    void _setValue(T newValue)
    {
        _value = newValue;
        valueSetChild();

        //qDebug() << "valueChanged" << logName() << newValue;
        emit valueChanged();
//      emit valueChanged777(_value);
    }

    static QString getName(QString sharedVariableName)
    {
        return sharedVariableName.split("/").last();
    }

    void sharedVariableUpdated()
    {
        _setValue(sharedVariable->value());
        emit valueChangedByNet();
    }

protected:
    virtual void valueSetChild()
    {

    }


//    void valueChanged777(T newValue);

};


#endif // CHANNEL_H
