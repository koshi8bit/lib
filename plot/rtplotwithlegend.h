#ifndef RTPLOTWITHLEGEND_H
#define RTPLOTWITHLEGEND_H

#include <QWidget>
#include <QDateTime>
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
    void configureAxis(RTPlotWithLegend::Axis axis, const QString &label, double min, double max, QCPAxis::ScaleType scaleType = QCPAxis::stLinear);


    bool realTime();
    double timeAxisRangeSEC();


    Graph *addGraph(RTPlotWithLegend::Axis axis, const QString &label);
    QCustomPlot *plot();

    static double now();


private:
    Ui::RTPlotWithLegend *ui;
    QCustomPlot *_plot;
    QCPItemLine *line;
    QVBoxLayout *legendLayout;
    bool _realTime;

    void configurePlotBackground();
    void configurePlotBackgroundAxis(QCPAxis *axis);
    void configurePlotZoomAndDrag(bool zoomAndDragTimeAxis);
    void configurePlotTimeAxis();
    void configurePlotLine();

    void configureLegend();

    ColorSetter colorSetter;

    QCPAxis *getAxis(Axis axis);

    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType);
    QVector<Graph *> graphElements;

signals:
    void realTimeChanged(bool newValue);

public slots:
    void mouseMove(double time);
    void setRealTime(bool newValue);

private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void mousePress(QMouseEvent *event);
    void mouseMove(QMouseEvent *event);
    void beforeReplot();


    
};


#endif // RTPLOTWITHLEGEND_H
