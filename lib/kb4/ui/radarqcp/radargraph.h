#ifndef RADARGRAPH_H
#define RADARGRAPH_H

#include <lib/qcustomplot/qcustomplot.h>

#include <lib/kb4/ui/radarqcp/abstractgraph.h>
#include <lib/kb4/ui/radarqcp/radarplot.h>

class RadarGraph : public AbstractGraph
{
public:
    RadarGraph(const QString &label, const QString &postfix, QColor color, RadarPlot *plot,
               int precision = 3, bool scientificNotation = false);

public slots:
    void setValue(double r, double angle);

private:
    RadarPlot *plot;
    QCPItemCurve *arrow;
};

#endif // RADARGRAPH_H
