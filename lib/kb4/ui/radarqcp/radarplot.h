#ifndef RADARQCP_H
#define RADARQCP_H

#include "abstractplot.h"
#include "radargraph.h"

class RadarPlot : public AbstractPlot
{
public:
    RadarPlot(QWidget *parent);

protected:
    void configurePlot() override;
    QPointF toPolar(double r, double angle);

private:
    QCPItemEllipse *criticalCircle;

    QCPItemEllipse *drawCircle(double radius, QColor color);
    void configureLines(double maxDiameter);

    // AbstractPlot interface
protected:
    AbstractGraph *abstractAddGraphGraph() override;
};

#endif // RADARQCP_H
