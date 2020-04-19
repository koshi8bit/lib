#ifndef REALTIMEGRAPH_H
#define REALTIMEGRAPH_H

#include <lib/kb4/ui/plots/base/abstractgraph.h>

class RealTimeGraph: public AbstractGraph
{
public:
    RealTimeGraph(const QString &label, const QString &postfix, QColor color,
                  QCustomPlot *qcp, int precision = 3,
                  bool scientificNotation = false);
};

#endif // REALTIMEGRAPH_H
