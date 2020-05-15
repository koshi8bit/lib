#ifndef SIMPLEPLOT_H
#define SIMPLEPLOT_H

#include <lib/kb4/ui/plots/base/abstractplot.h>
#include <lib/kb4/ui/plots/simple/simplegraph.h>

class SimplePlot : public AbstractPlot
{
public:
    SimplePlot(QWidget *parent);

    SimpleGraph *addGraph(const QString &label, const QString &postfix = "", bool yAxis2 = false,
                         int precision = 3, bool scientificNotation = false);


    // AbstractPlot interface
protected:
    void configurePlot() override;
};

#endif // SIMPLEPLOT_H
