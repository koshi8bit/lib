#ifndef REALTIMEPLOT_H
#define REALTIMEPLOT_H

#include <lib/kb4/ui/plots/base/abstractplot.h>
#include <lib/kb4/ui/plots/base/axisconfig.h>
#include <lib/kb4/ui/plots/realtime/realtimegraph.h>

class RealTimePlot : public AbstractPlot
{
    Q_OBJECT
public:
    RealTimePlot(QWidget *parent);
    ~RealTimePlot() override;
    static double currentDateTime();
    static double dateTimeToKey(QDateTime dt);
    static QDateTime keyToDateTime(double key);

    void configureAxis(QCPAxis *axis, const QString &label, const QString &postfix = "", double min=0, double max=100, int precision = 0, QCPAxis::ScaleType scaleType = QCPAxis::stLinear);
    RealTimeGraph* addGraph(const QString &label, const QString &postfix = "", int precision = 3, bool scientificNotation = false);
    RealTimeGraph* addGraph(QCPAxis *axis, const QString &label, const QString &postfix = "", int precision = 3, bool scientificNotation = false);
    //Graph* addGraph(ChannelDouble *channel, bool visible = true);
    //void removeGraph(QCPGraph *graph);
    void removeGraphs();
    void removeGraph(RealTimeGraph *graph);

    void setTimeAxisRange(int newRangeMSEC);
    void setTimeLabelVisible(bool newValue);

    void setMarginGroup(QCPMarginGroup *mg);

    bool realTime() const;
    bool moveLineRealTime() const;
    void setCursor2Visible(bool newValue, RealTimePlot *senderWidget);
    void setCursor2Key(double key, RealTimePlot *senderWidget);
    void setMoveLineRealTime(bool newValue, RealTimePlot *senderWidget);
    void setRealTime(bool newValue, RealTimePlot *senderWidget);
    void setCursorKey(double key, RealTimePlot *senderWidget);
    void setTimeAxisRange(const QCPRange &newRange, RealTimePlot *senderWidget);
    //void moveCursor(double time, RealTimeQCP *senderWidget);

    void configureTimerReplot(int intervalMSEC = 10);

    QCPItemLine *cursor2() const;


    bool dayStyle() const;
    void setDayStyle(bool dayStyle, bool showTime = true);





signals:
    void cursor2VisibleValueChanged(bool newValue);
    void moveLineRealTimeChanged(bool newValue);
    void realTimeChanged(bool newValue);
    void cursorKeyChanged(double key);
    void cursor2KeyChanged(double key);
    void timeAxisRangeChanged(const QCPRange &newRange);

public slots:
    void setRealTime(bool newValue);
    bool cursor2Visible();
    void setMoveLineRealTime(bool newValue);
    void setCursorKey(double time);
    void moveTimeAxisRealTime();
    void setCursor2Visible(bool newValue);
    void setCursor2Key(double key);
    void setTimeAxisRange(const QCPRange &newValue);

private:
    RealTimeGraph* graphCast(AbstractGraph* graph);

    bool _realTime;
    bool _moveLineRealTime;
    bool _dayStyle = false;

    QCPItemText *statusLabel;
    QTimer *timerReplot;

    //TODO make 2 lines same as oscillograph switching by Mouse wheel button
    QCPItemLine *_cursor;
    QCPItemLine *_cursor2;
    //bool _cursor2CanMove = false;

    void _configurePlot();
    void configurePlotTimeAxis();
    void configurePlotLine();
    void configurePlotLine(QCPItemLine **line);

    void configureAxesZoomAndDrag(bool configureYAxises);


    void updateTimeAxisLabel();

    void configureSplitter();
    QSplitter *splitter;

    QLabel *labelTime;
    const QString timeLabel = tr("Время");

    QString formatLabelTime(double key);

    bool isInAxisRect(QPoint pos);

    double timeAxisOldRange;

    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType);

    void _setCursor2Visible(bool newValue);
    void _setCursor2Key(double key);

    double getYAxisUpper();
    double getYAxisLower();


    void _setRealTime(bool newValue);
    void _setMoveLineRealTime(bool newValue);

    void _setCursorKey(double time);

    void configureStatusLabel();
    void updateStatusLabel();
    bool updateStatusLabelFlag = false;

private slots:

    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);

    void mouseMove(QMouseEvent *event);
    void mousePress(QMouseEvent *event);
    void mouseDoubleClick(QMouseEvent *event);
    void mouseWheel(QWheelEvent *event);

    void beforeReplot();
    void _setTimeAxisRange(const QCPRange &newRange);

    // AbstractPlot interface
protected:
    void configurePlot() override;
};

#endif // REALTIMEPLOT_H
