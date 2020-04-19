#ifndef REALTMEPLOT_H
#define REALTMEPLOT_H

#include <lib/kb4/ui/plots/base/abstractplot.h>

class RealTmePlot : public AbstractPlot
{
public:
    RealTmePlot(QWidget *parent);

    bool realTime() const;
    void setRealTime(bool newValue, RealTmePlot *senderWidget);

protected:
    void configurePlot() override;

signals:
    void realTimeChanged(bool newValue);

public slots:
    void setRealTime(bool newValue);

private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);

    void mouseMove(QMouseEvent *event);
    void mousePress(QMouseEvent *event);
    void mouseDoubleClick(QMouseEvent *event);
    void mouseWheel(QWheelEvent *event);

    void beforeReplot();
    void _setTimeAxisRange(const QCPRange &newRange);

private:
    QCPItemText *statusLabel;
    void configureStatusLabel();
    bool updateStatusLabelFlag = false;
    void updateStatusLabel();

    void _configurePlot();
    void configureAxesZoomAndDrag(bool configureYAxises);

    bool _realTime, _moveLineRealTime, _dayStyle = false;
    void _setRealTime(bool newValue);

    const QString timeLabel = tr("Время");

    void _setCursor2Visible(bool newValue);
};

#endif // REALTMEPLOT_H
