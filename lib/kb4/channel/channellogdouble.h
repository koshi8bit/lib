#ifndef CHANNELDOUBLE_H
#define CHANNELDOUBLE_H

#include "channellogt.h"

#include <lib/kb4/ui/rtplotwithlegend/rtplotwithlegend.h>
#include <lib/kb4/ui/rtplotwithlegend/graph.h>

class ChannelLogDouble : public ChannelLogT<double>
{
public:
    ChannelLogDouble(QString name, QString postfix, QStringList *path, QObject *parent = nullptr);
    void setGraph(Graph *graph);
private:
    Graph *graph;

private slots:
    void addDataToGraph();
};

#endif // CHANNELDOUBLE_H
