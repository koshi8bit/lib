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
    void setYAxisLabel(const QString &label, QCPAxis::ScaleType type = QCPAxis::stLinear);
    void setYAxis2Label(const QString &label, QCPAxis::ScaleType type = QCPAxis::stLinear);

    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType type);

    QCustomPlot* getPlot();

private:
    Ui::RTPlotWithLegend *ui;
    QCustomPlot *plot;
    QCPItemLine *line;

    void configurePlotZoomAndDrag(bool zoomAndDragTimeAxis);
    void configurePlotBackground();
    void configurePlotBackgroundAxis(QCPAxis *axis);
    void configurePlotTimeAxis();
    void configurePlotLine();

private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void mouseMove(QMouseEvent *event);
};

#endif // RTPLOTWITHLEGEND_H
