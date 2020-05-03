#include "channelbool.h"

ChannelBool::ChannelBool(QString name, QString postfix, QObject *parent)
    :ChannelRealTimeGraph<bool>(name, postfix, parent)
{
    configure();
}

ChannelBool::ChannelBool(QString name, QString postfix, QStringList &path, QObject *parent)
    :ChannelRealTimeGraph<bool>(name, postfix, path, parent)
{
    configure();
}

ChannelBool::ChannelBool(QString sharedVariableName, QObject *parent)
    :ChannelRealTimeGraph<bool>(sharedVariableName, parent)
{
    configure();
}

ChannelBool::~ChannelBool()
{

}

void ChannelBool::configure()
{
    connect(this, &Channel::valueChanged, [this]() { emit valueChangedDouble(value()); } );
    setScientificNotation(false);
    setPrecision(0);
}

void ChannelBool::valueChangedChild()
{
    if (realTimeGraph() != nullptr) { realTimeGraph()->addData(RealTimePlot::currentDateTime(), this->value()); }
}


