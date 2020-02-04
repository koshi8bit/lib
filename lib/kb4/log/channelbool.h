#ifndef CHANNELBOOL_H
#define CHANNELBOOL_H

#include "channelt.h"

#include <lib/kb4/ui/realtimeqcp/realtimeqcp.h>
#include <lib/kb4/ui/realtimeqcp/graph.h>

class ChannelBool : public ChannelT<bool>
{
    Q_OBJECT
public:
    ChannelBool(QString name, QString postfix, QObject *parent = nullptr);
    ChannelBool(QString name, QString postfix, QStringList &path, QObject *parent = nullptr);
    ChannelBool(QString sharedVariableName, QObject *parent = nullptr);

    void addGraphToPlot(RealTimeQCP *plot, bool visible=true);
    Graph *graph() const;

private:
    Graph *_graph = nullptr;
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
