#ifndef CHANNELDOUBLE_H
#define CHANNELDOUBLE_H

#include "channelt.h"

#include <lib/kb4/ui/rtplotwithlegend/rtplotwithlegend.h>
#include <lib/kb4/ui/rtplotwithlegend/graph.h>

class ChannelDouble : public ChannelT<double>
{
public:
    ChannelDouble(QString name, QString postfix, QStringList *path, QObject *parent = nullptr);
    void setGraph(Graph *graph);
    bool isScientificNotation();
    void setScientificNotation(bool newValue);
private:
    Graph *graph;
    bool _scientificNotation = false;

private slots:
    void addDataToGraph();
};

#endif // CHANNELDOUBLE_H
