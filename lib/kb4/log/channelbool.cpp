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
    _graph = plot->addGraph(plotName(), postfix(), 0);
    _graph->setVisible(visible);
    if (color().isValid())
        _graph->setColor(color());
}


RealTimeGraph *ChannelBool::graph() const
{
    return _graph;
}

void ChannelBool::configure()
{
    connect(this, &Channel::valueChanged, [this]() { emit valueChangedDouble(value()); } );
}

void ChannelBool::valueChangedChild()
{
    if (_graph != nullptr) { _graph->addData(RealTimePlot::currentDateTime(), value()); }
}

void ChannelBool::_valueChanged()
{
    //TODO: template fuck
    //emit valueChangedDouble(value());
}

