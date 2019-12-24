#ifndef REALTIMEQCP_H
#define REALTIMEQCP_H

#include <QWidget>

#include <lib/qcustomplot/qcustomplot.h>

#include <lib/kb4/easyliving.h>

#include "axisconfig.h"
#include "graph.h"

namespace Ui {
class RealTimeQCP;
}

class RealTimeQCP : public QWidget
{
    Q_OBJECT

public:
    explicit RealTimeQCP(QWidget *parent = nullptr);
    ~RealTimeQCP();

    static double currentDateTime();

    void configureAxis(QCPAxis *axis, const QString &label, double min, double max, QCPAxis::ScaleType scaleType = QCPAxis::stLinear, int precision = 3);

    QCustomPlot* plot() const;
    void moveTimeAxisRealTime();
    void setTimeAxisRange(int newRangeSEC);

    void setMarginGroup(QCPMarginGroup *mg);

    bool realTime() const;
    bool moveLineRealTime() const;

signals:
    void lineRealTimeMoved();
    void moveLineRealTimeChanged(bool newValue);
    void realTimeChanged(bool newValue);

public slots:
    void setRealTime(bool newValue);

    //? what is this? rename?
    void setMoveLineRealTime(bool moveLineRealTime);
    void mouseMove(double time);

private:
    Ui::RealTimeQCP *ui;

    bool _realTime;
    bool _moveLineRealTime;
    const QString timeLabel = tr("Время");

    //TODO rename to _lineA
    //TODO make 2 lines same as oscillograph
    QCPItemLine *_line;
    QCPItemLine *_lineB;

    void configurePlot();
    void configureAxesZoomAndDrag(bool configureTimeAxis);
    void configurePlotBackground();
    void configurePlotBackgroundAxis(QCPAxis *axis);
    void configurePlotTimeAxis();
    void configurePlotLine();

    void updateTimeAxisLabel();

    void configureLegend();
    QVBoxLayout *_legendLayout;
    QLabel *_labelTime;

    void autoScaleAxis(QCPAxis *axis);

    //WARNING rename to _graphs?
    QVector<Graph *> _graphElements;
    static QString formatLabelTime(double time);

    bool isInAxisRect(QPoint pos);

    double timeAxisOldRange;

    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType);

private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);

    void mouseMove(QMouseEvent *event);
    void mousePress(QMouseEvent *event);
    void mouseDoubleClick(QMouseEvent *event);

    void beforeReplot();
    void timeAxisRangeChanged(const QCPRange &newRange);

};

#endif // REALTIMEQCP_H