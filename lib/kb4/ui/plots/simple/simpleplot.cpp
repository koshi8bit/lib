#include "simpleplot.h"

SimplePlot::SimplePlot(QWidget *parent)
{
    configurePlot();
}

void SimplePlot::configurePlot()
{
    qcp()->setInteraction(QCP::iRangeZoom, true);
    qcp()->setInteraction(QCP::iRangeDrag, true);
    configurePlotBackground();
}
