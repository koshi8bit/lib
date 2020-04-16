#ifndef RADARGRAPH_H
#define RADARGRAPH_H

#include <lib/qcustomplot/qcustomplot.h>

#include <lib/kb4/ui/radarqcp/abstractgraph.h>

class RadarGraph : public AbstractGraph
{
public:
    static QPointF toPolar(double r, double angle);
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

    // AbstractGraph interface
protected:
    void abstractSetVisible(bool newValue) override;
    void abstractSetColor(QColor newValue) override;
};

#endif // RADARGRAPH_H
