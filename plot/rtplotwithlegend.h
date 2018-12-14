#ifndef RTPLOTWITHLEGEND_H
#define RTPLOTWITHLEGEND_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class RTPlotWithLegend;
}

class RTPlotWithLegend : public QWidget
{
    Q_OBJECT

public:
    explicit RTPlotWithLegend(QWidget *parent = nullptr);
    ~RTPlotWithLegend();
    void setMarginGroup(QCPMarginGroup *mg);

private:
    Ui::RTPlotWithLegend *ui;

    void configurePlotZoomAndDrag(QCustomPlot *plot, bool zoomAndDragTimeAxis);
    void configurePlotBackground(QCustomPlot *plot);
};

#endif // RTPLOTWITHLEGEND_H
