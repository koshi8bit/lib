#ifndef RTPLOTWITHLEGEND_H
#define RTPLOTWITHLEGEND_H

#include <QWidget>
#include "qcustomplot.h"
#include "axisconfig.h"
#include "colorsetter.h"
#include "graphelement.h"

namespace Ui {
class RTPlotWithLegend;
}

class RTPlotWithLegend : public QWidget
{
    Q_OBJECT

public:
    enum Axis
    {
        yAxis,
        yAxis2
    };
    Q_ENUMS(Axis)

    explicit RTPlotWithLegend(QWidget *parent = nullptr);
    virtual ~RTPlotWithLegend();
    void setMarginGroup(QCPMarginGroup *mg);
    void setAxisLabel(Axis axis, const QString &label, QCPAxis::ScaleType type = QCPAxis::stLinear);

    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType type);
    void configurePlotZoomAndDrag(bool zoomAndDragTimeAxis);

    GraphElement *addGraph(Axis axis, const QString &label);
    QCustomPlot *getPlot();

private:
    Ui::RTPlotWithLegend *ui;
    QCustomPlot *plot;
    QCPItemLine *line;

    void configurePlotBackground();
    void configurePlotBackgroundAxis(QCPAxis *axis);
    void configurePlotTimeAxis();
    void configurePlotLine();
    ColorSetter colorSetter;

    QCPAxis *getAxis(Axis axis);

    QVector<GraphElement *> graphElements;

private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void mouseMove(QMouseEvent *event);
};

#endif // RTPLOTWITHLEGEND_H
