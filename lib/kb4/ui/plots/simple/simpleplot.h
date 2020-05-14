#ifndef SIMPLEPLOT_H
#define SIMPLEPLOT_H

#include <lib/kb4/ui/plots/base/abstractplot.h>

class SimplePlot : public AbstractPlot
{
public:
    SimplePlot(QWidget *parent);

    // AbstractPlot interface
protected:
    void configurePlot() override;
};

#endif // SIMPLEPLOT_H
