#ifndef REALTIMEQCP_H
#define REALTIMEQCP_H

#include <QWidget>

#include <lib/qcustomplot/qcustomplot.h>

#include <lib/kb4/easyliving.h>

#include "axisconfig.h"

namespace Ui {
class RealTimeQCP;
}

class RealTimeQCP : public QWidget
{
    Q_OBJECT

public:
    explicit RealTimeQCP(QWidget *parent = nullptr);
    ~RealTimeQCP();

    bool realTime() const;

    bool moveLineRealTime() const;
    QCustomPlot* plot() const;

    void setTimeAxisRange(int newRangeSEC);

    static double currentDateTime();

public slots:
    void setRealTime(bool newValue);

    //? what is this? rename?
    void setMoveLineRealTime(bool moveLineRealTime);

private:
    Ui::RealTimeQCP *ui;

    bool _realTime;
    bool _moveLineRealTime;
    const QString timeLabel = tr("Время");

    QCPItemLine *_line;

    void configurePlot();
    void configureAxesZoomAndDrag(bool configureTimeAxis);
    void configurePlotBackground();
    void configurePlotBackgroundAxis(QCPAxis *axis);
    void configurePlotTimeAxis();
    void configurePlotLine();

    void updateTimeAxisRangePostfix();

    void configureLegend();
    QVBoxLayout *_legendLayout;
    QLabel *_labelTime;

    void autoScaleAxis(QCPAxis *axis);

private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);

    void mouseMove(QMouseEvent *event);
    void mousePress(QMouseEvent *event);
    void mouseDoubleClick(QMouseEvent *event);

    void beforeReplot();
    void xAxisRangeChanged(const QCPRange &newRange);

};

#endif // REALTIMEQCP_H
