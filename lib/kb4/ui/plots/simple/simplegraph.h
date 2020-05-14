#ifndef SIMPLEGRAPH_H
#define SIMPLEGRAPH_H

#include <lib/kb4/ui/plots/base/abstractgraph.h>

class SimpleGraph: public AbstractGraph
{
public:
    SimpleGraph(const QString &label, const QString &postfix, QColor color,
                QCustomPlot *qcp, QCPAxis *yAxis, int precision = 3,
                bool scientificNotation = false);

    ~SimpleGraph() override;

    // AbstractGraph interface
protected:
    void updateLegendItem() override;
    void abstractSetVisible() override;
    void abstractSetColor() override;
};


#endif // SIMPLEGRAPH_H
