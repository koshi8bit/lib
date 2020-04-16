#ifndef RADARGRAPH_H
#define RADARGRAPH_H

#include <lib/qcustomplot/qcustomplot.h>

#include <lib/kb4/ui/radarqcp/abstractgraph.h>
#include <lib/kb4/ui/radarqcp/radarplot.h>

class RadarGraph : public AbstractGraph
{
public:
    RadarGraph(const QString &label, const QString &postfix, QColor color, QCustomPlot *qcp,
               int precision = 3, bool scientificNotation = false);

    double radius() const;
    void setRadius(double radius);

    double angle() const;
    void setAngle(double angle);

public slots:
    void setValue(double radius, double angle);

private:
    //RadarPlot *plot;
    QCPItemCurve *arrow;
    double _radius=0, _angle=0;
    void redrawArrow();
};

#endif // RADARGRAPH_H
