#ifndef REALTIMEQCP_H
#define REALTIMEQCP_H

//https://github.com/koshi8bit/lib

#include <QWidget>

#include <lib/qcustomplot/qcustomplot.h>

#include <lib/kb4/easyliving.h>
//#include <lib/kb4/log/channeldouble.h>

#include "axisconfig.h"
#include "graph.h"
#include "colorsetter.h"

//FIXME в графе хранить ссылку на channel?


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
    static double dateTimeToKey(QDateTime dt);

    void configureAxis(QCPAxis *axis, const QString &label, const QString &postfix, double min, double max, int precision = 0, QCPAxis::ScaleType scaleType = QCPAxis::stLinear);
    Graph* addGraph(const QString &label, const QString &postfix = "", int precision = 3, bool scientificNotation = false);
    Graph* addGraph(QCPAxis *axis, const QString &label, const QString &postfix = "", int precision = 3, bool scientificNotation = false);
    //Graph* addGraph(ChannelDouble *channel, bool visible = true);

    QCustomPlot* plot() const;

    void setTimeAxisRange(int newRangeMSEC);
    void setTimeLabelVisible(bool newValue);

    void setMarginGroup(QCPMarginGroup *mg);

    bool realTime() const;
    bool moveLineRealTime() const;
    void setCursor2Visible(bool newValue, RealTimeQCP *senderWidget);
    void setCursor2Key(double key, RealTimeQCP *senderWidget);
    void setMoveLineRealTime(bool newValue, RealTimeQCP *senderWidget);
    void setRealTime(bool newValue, RealTimeQCP *senderWidget);
    void setCursorKey(double key, RealTimeQCP *senderWidget);
    void setTimeAxisRange(const QCPRange &newRange, RealTimeQCP *senderWidget);
    //void moveCursor(double time, RealTimeQCP *senderWidget);




    QCPItemLine *cursor2() const;
    void autoScaleAxis(QCPAxis *axis);


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
    Ui::RealTimeQCP *ui;

    bool _realTime;
    bool _moveLineRealTime;
    const QString timeLabel = tr("Время");

    QCPItemText *statusLabel;

    //TODO make 2 lines same as oscillograph switching by Mouse wheel button
    QCPItemLine *_cursor;
    QCPItemLine *_cursor2;
    //bool _cursor2CanMove = false;

    void configurePlot();
    void configureAxesZoomAndDrag(bool configureYAxises);
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


    //WARNING rename to _graphs?
    QVector<Graph *> graphs;
    QString formatLabelTime(double time);

    bool isInAxisRect(QPoint pos);

    double timeAxisOldRange;

    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType);
    ColorSetter colorSetter;

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
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);

    void mouseMove(QMouseEvent *event);
    void mousePress(QMouseEvent *event);
    void mouseDoubleClick(QMouseEvent *event);
    void mouseWheel(QMouseEvent *event);

    void beforeReplot();
    void _setTimeAxisRange(const QCPRange &newRange);

    void on_pushButton_clicked();
};

#endif // REALTIMEQCP_H
