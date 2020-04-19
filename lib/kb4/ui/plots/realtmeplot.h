#ifndef REALTMEPLOT_H
#define REALTMEPLOT_H

#include <lib/kb4/ui/plots/abstractplot.h>
#include <lib/kb4/ui/plots/radargraph.h>

class RealTmePlot : public AbstractPlot
{
public:
    RealTmePlot(QWidget *parent);

protected:
    void configurePlot() override;

private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);

    void mouseMove(QMouseEvent *event);
    void mousePress(QMouseEvent *event);
    void mouseDoubleClick(QMouseEvent *event);
    void mouseWheel(QWheelEvent *event);

    void beforeReplot();
    void _setTimeAxisRange(const QCPRange &newRange);
};

#endif // REALTMEPLOT_H
