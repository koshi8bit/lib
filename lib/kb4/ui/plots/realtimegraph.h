#ifndef REALTIMEGRAPH_H
#define REALTIMEGRAPH_H

#include <lib/qcustomplot/qcustomplot.h>

#include <lib/kb4/ui/plots/base/abstractgraph.h>

class RealTimeGraph: public AbstractGraph
{
public:
    RealTimeGraph(const QString &label, const QString &postfix, QColor color,
                  QCustomPlot *qcp, QCPAxis *yAxis, int precision = 3,
                  bool scientificNotation = false);

    // AbstractGraph interface
protected:
    void abstractSetVisible(bool newValue) override;
    void abstractSetColor(QColor newValue) override;
};

#endif // REALTIMEGRAPH_H
