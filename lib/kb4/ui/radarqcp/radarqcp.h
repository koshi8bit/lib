#ifndef RADARQCP_H
#define RADARQCP_H

#include "qcpwithlegend.h"

class RadarQcp : public QcpWithLegend
{
public:
    RadarQcp(QWidget *parent);

protected:
    void configurePlot() override;
    QPointF toPolar(double r, double angle);

private:
    QCPItemEllipse *criticalCircle;

    QCPItemEllipse *drawCircle(double radius, QColor color);
    void configureLines(double maxDiameter);
};

#endif // RADARQCP_H
