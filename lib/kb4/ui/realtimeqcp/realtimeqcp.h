#ifndef REALTIMEQCP_H
#define REALTIMEQCP_H

#include <QWidget>

#include <lib/qcustomplot/qcustomplot.h>

#include <lib/kb4/easyliving.h>
//#include <lib/kb4/log/channeldouble.h>

#include "axisconfig.h"
#include "graph.h"
#include "colorsetter.h"

//f8f1856 - old widget

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

    void configureAxis(QCPAxis *axis, const QString &label, const QString &postfix, double min, double max, int precision = 0, QCPAxis::ScaleType scaleType = QCPAxis::stLinear);
    Graph* addGraph(const QString &label, const QString &postfix = "", int precision = 3, bool scientificNotation = false);
    Graph* addGraph(QCPAxis *axis, const QString &label, const QString &postfix = "", int precision = 3, bool scientificNotation = false);
    //Graph* addGraph(ChannelDouble *channel, bool visible = true);

    QCustomPlot* plot() const;

    void setTimeAxisRange(int newRangeSEC);
    void setTimeLabelVisible(bool newValue);

    void setMarginGroup(QCPMarginGroup *mg);

    bool realTime() const;
    bool moveLineRealTime() const;

signals:
    void lineRealTimeMoved();
    void moveLineRealTimeChanged(bool newValue);
    void realTimeChanged(bool newValue);

public slots:
    void setRealTime(bool newValue);

    bool cursor2Visible();
    void setCursor2Visible(bool newValue);
    void setMoveLineRealTime(bool moveLineRealTime);
    void moveCursor(double time);
    void moveTimeAxisRealTime();

private:
    Ui::RealTimeQCP *ui;

    bool _realTime;
    bool _moveLineRealTime;
    const QString timeLabel = tr("Время");

    //TODO make 2 lines same as oscillograph switching by Mouse wheel button
    QCPItemLine *_cursor;
    QCPItemLine *_cursor2;
    //bool _cursor2CanMove = false;

    void configurePlot();
    void configureAxesZoomAndDrag(bool configureTimeAxis);
    void configurePlotBackground();
    void configurePlotBackgroundAxis(QCPAxis *axis);
    void configurePlotTimeAxis();
    void configurePlotLine();
    void configurePlotLine(QCPItemLine **line);

    void updateTimeAxisLabel();

    void configureLegend();
    QVBoxLayout *legendLayout;
    QLabel *labelTime;

    void configureSplitter();
    QSplitter *splitter;

    void autoScaleAxis(QCPAxis *axis);

    //WARNING rename to _graphs?
    QVector<Graph *> graphs;
    static QString formatLabelTime(double time);

    bool isInAxisRect(QPoint pos);

    double timeAxisOldRange;

    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType);
    ColorSetter colorSetter;

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
