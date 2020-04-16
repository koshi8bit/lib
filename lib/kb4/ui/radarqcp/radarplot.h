#ifndef RADARQCP_H
#define RADARQCP_H

#include "abstractplot.h"
#include "radargraph.h"

class RadarPlot : public AbstractPlot
{
public:
    RadarPlot(QWidget *parent);
    static QPointF toPolar(double r, double angle);

    RadarGraph *addGraph(const QString &label, const QString &postfix = "", int precision = 3, bool scientificNotation = false);

protected:
    void configurePlot() override;

private:
    QCPItemEllipse *criticalCircle;

    QCPItemEllipse *drawCircle(double radius, QColor color);
    void configureLines(double maxDiameter);


};

#endif // RADARQCP_H
