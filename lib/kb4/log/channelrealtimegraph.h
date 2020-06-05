#ifndef CHANNELREALTIMEGRAPH_H
#define CHANNELREALTIMEGRAPH_H


#include <lib/kb4/ui/plots/realtime/realtimeplot.h>
#include <lib/kb4/ui/plots/realtime/realtimegraph.h>

#include "channelt.h"

template <typename T>
class ChannelRealTimeGraph : public ChannelT<T>
{
    //Q_OBJECT
public:
    ChannelRealTimeGraph(QString name, QString postfix, QObject *parent = nullptr)
        :ChannelT<T>(name, postfix, parent)
    {

    }

    ChannelRealTimeGraph(QString name, QString postfix, QStringList &path, QObject *parent = nullptr)
        :ChannelT<T>(name, postfix, path, parent)
    {

    }

    ChannelRealTimeGraph(QString sharedVariableName, QObject *parent = nullptr)
        :ChannelT<T>(sharedVariableName, parent)
    {

    }

    ~ChannelRealTimeGraph()
    {
        if (realTimeGraph())
            realTimePlot()->removeGraph(realTimeGraph());

        if (realTimeGraph())
            delete realTimeGraph();
    }

    void addGraphToPlot(RealTimePlot *plot, bool visible=true)
    {
        addGraphToPlot(plot, plot->qcp()->yAxis, visible);
    }

    void addGraphToPlot(RealTimePlot *plot, QCPAxis *axis, bool visible=true)
    {
        _realTimePlot = plot;
        _realTimeGraph = plot->addGraph(axis, this->plotName(), this->postfix(),
                                        precision(), scientificNotation());
        _realTimeGraph->setVisible(visible);
        if (this->color().isValid())
            _realTimeGraph->setColor(this->color());
    }

    bool scientificNotation() const
    {
        return _scientificNotation;
    }

    void setScientificNotation(bool newValue)
    {
        _scientificNotation = newValue;
    }

    int precision() const
    {
        return _precision;
    }

    void setPrecision(int precision)
    {
        _precision = precision;
    }

    int precisionLog() const
    {
        return _precision;
    }

    void setPrecisionLog(int precision)
    {
        _precision = precision;
    }

    RealTimeGraph *realTimeGraph()
    {
        return _realTimeGraph;
    }

    RealTimePlot *realTimePlot()
    {
        return _realTimePlot;
    }

private:
    RealTimeGraph *_realTimeGraph = nullptr;
    RealTimePlot *_realTimePlot = nullptr;

    int _precision, _precisionLog;
    bool _scientificNotation = false;
};


#endif // CHANNELREALTIMEGRAPH_H
