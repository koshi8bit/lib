#ifndef RTPLOTWITHLEGEND_H
#define RTPLOTWITHLEGEND_H

#include <QWidget>
#include "qcustomplot.h"
#include "axisconfig.h"

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
    void setYAxisLabel(const QString &label);
    void setYAxis2Label(const QString &label);

    QCustomPlot* getPlot();

private:
    Ui::RTPlotWithLegend *ui;
    QCustomPlot *plot;
    QCPItemLine *line;

    void configurePlotZoomAndDrag(QCustomPlot *plot, bool zoomAndDragTimeAxis);
    void configurePlotBackground(QCustomPlot *plot);
    void configurePlotBackgroundAxis(QCPAxis *axis);
    void configurePlotTimeAxis(QCustomPlot *plot);
    void configurePlotLine(QCustomPlot *plot);

private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void mouseMove(QMouseEvent *event);
};

#endif // RTPLOTWITHLEGEND_H
