#ifndef CHANNELDOUBLE_H
#define CHANNELDOUBLE_H

#include "channelt.h"

#include <lib/kb4/ui/rtplotwithlegend/rtplotwithlegend.h>
#include <lib/kb4/ui/rtplotwithlegend/graph.h>

class ChannelDouble : public ChannelT<double>
{
public:
    ChannelDouble(QString displayName, QStringList logName, QObject *parent = nullptr);
    void setGraph(Graph *graph);
private:
    Graph *graph;

private slots:
    void addDataToGraph();
};

#endif // CHANNELDOUBLE_H
