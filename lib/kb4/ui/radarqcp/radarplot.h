#ifndef RADARPLOT_H
#define RADARPLOT_H

#include <lib/kb4/ui/radarqcp/abstractplot.h>
#include <lib/kb4/ui/radarqcp/radargraph.h>

class RadarPlot : public AbstractPlot
{
public:
    RadarPlot(QWidget *parent);
    static QPointF toPolar(double r, double angle);

    RadarGraph *addGraph(const QString &label, const QString &postfix = "",
                         int precision = 3, bool scientificNotation = false, int width = 1);

protected:
    void configurePlot() override;

private:
    QCPItemEllipse *criticalCircle;

    QCPItemEllipse *drawCircle(double radius, QColor color);
    void configureLines(double maxDiameter);


};

#endif // RADARPLOT_H
