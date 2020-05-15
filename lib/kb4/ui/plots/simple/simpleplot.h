#ifndef SIMPLEPLOT_H
#define SIMPLEPLOT_H

#include <lib/kb4/ui/plots/base/abstractplot.h>
#include <lib/kb4/ui/plots/simple/simplegraph.h>
#include <lib/kb4/ui/plots/simple/errorygraph.h>
#include <lib/kb4/ui/plots/simple/errorxygraph.h>

class SimplePlot : public AbstractPlot
{
public:
    SimplePlot(QWidget *parent);

    SimpleGraph *addGraph(const QString &label, const QString &postfix = "", bool yAxis2 = false,
                         int precision = 3, bool scientificNotation = false);

    ErrorYGraph *addGraphErrorY(const QString &label, const QString &postfix = "", bool yAxis2 = false,
                         int precision = 3, bool scientificNotation = false);

    ErrorXYGraph *addGraphErrorXY(const QString &label, const QString &postfix = "", bool yAxis2 = false,
                         int precision = 3, bool scientificNotation = false);

    void configureAxis(bool yAxis2, const QString &label, const QString &postfix = "", double min=0, double max=100, int precision = 0, QCPAxis::ScaleType scaleType = QCPAxis::stLinear);
    void configureAxis(QCPAxis *axis, const QString &label, const QString &postfix = "", double min=0, double max=100, int precision = 0, QCPAxis::ScaleType scaleType = QCPAxis::stLinear);

    // AbstractPlot interface
protected:
    void configurePlot() override;

private:
    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType);
};

#endif // SIMPLEPLOT_H
