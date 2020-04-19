#ifndef CHANNELBOOL_H
#define CHANNELBOOL_H

#include "channelt.h"

#include <lib/kb4/ui/plots/realtimeplot.h>
#include <lib/kb4/ui/plots/realtimegraph.h>

class ChannelBool : public ChannelT<bool>
{
    Q_OBJECT
public:
    ChannelBool(QString name, QString postfix, QObject *parent = nullptr);
    ChannelBool(QString name, QString postfix, QStringList &path, QObject *parent = nullptr);
    ChannelBool(QString sharedVariableName, QObject *parent = nullptr);

    void addGraphToPlot(RealTimePlot *plot, bool visible=true);
    RealTimeGraph *graph() const;

private:
    RealTimeGraph *_graph = nullptr;
    void configure();

signals:
    //TODO: template fuck
    //void valueChangedDouble(double newValue);

protected:
    void valueChangedChild() override;
    void _valueChanged();
private slots:
};

#endif // CHANNELBOOL_H
