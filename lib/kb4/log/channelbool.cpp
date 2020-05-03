#include "channelbool.h"

ChannelBool::ChannelBool(QString name, QString postfix, QObject *parent)
    :ChannelT<bool>(name, postfix, parent)
{
    configure();
}

ChannelBool::ChannelBool(QString name, QString postfix, QStringList &path, QObject *parent)
    :ChannelT<bool>(name, postfix, path, parent)
{
    configure();
}

ChannelBool::ChannelBool(QString sharedVariableName, QObject *parent)
    :ChannelT<bool>(sharedVariableName, parent)
{
    configure();
}

ChannelBool::~ChannelBool()
{

}

void ChannelBool::addGraphToPlot(RealTimePlot *plot, bool visible)
{
    _realTimeGraph = plot->addGraph(plotName(), postfix(), 0);
    _realTimeGraph->setVisible(visible);
    if (color().isValid())
        _realTimeGraph->setColor(color());
}


RealTimeGraph *ChannelBool::realTimeGraph() const
{
    return _realTimeGraph;
}

void ChannelBool::configure()
{
    connect(this, &Channel::valueChanged, [this]() { emit valueChangedDouble(value()); } );
}

void ChannelBool::valueChangedChild()
{
    if (_realTimeGraph != nullptr) { _realTimeGraph->addData(RealTimePlot::currentDateTime(), value()); }
}

void ChannelBool::_valueChanged()
{
    //TODO: template fuck
    //emit valueChangedDouble(value());
}

