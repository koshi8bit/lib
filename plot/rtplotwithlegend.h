#ifndef RTPLOTWITHLEGEND_H
#define RTPLOTWITHLEGEND_H

#include <QWidget>
#include "qcustomplot.h"
#include "axisconfig.h"
#include "colorsetter.h"
#include "graph.h"

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
    void setAxisLabel(RTPlotWithLegend::Axis axis, const QString &label, QCPAxis::ScaleType scaleType = QCPAxis::stLinear);

    void configurePlotZoomAndDrag(bool zoomAndDragTimeAxis);

    Graph *addGraph(RTPlotWithLegend::Axis axis, const QString &label);
    QCustomPlot *plot();

private:
    Ui::RTPlotWithLegend *ui;
    QCustomPlot *_plot;
    QCPItemLine *line;
    QVBoxLayout *legendLayout;

    void configurePlotBackground();
    void configurePlotBackgroundAxis(QCPAxis *axis);
    void configurePlotTimeAxis();
    void configurePlotLine();

    void configureLegend();

    ColorSetter colorSetter;

    QCPAxis *getAxis(Axis axis);

    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType);
    QVector<Graph *> graphElements;

public slots:
    void mouseMove(double time);

private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void mouseMove(QMouseEvent *event);

};

#endif // RTPLOTWITHLEGEND_H
