#ifndef ABSTRACTPLOT_H
#define ABSTRACTPLOT_H

#include <QWidget>

#include <lib/qcustomplot/qcustomplot.h>
#include <lib/kb4/ui/printscreener/printscreener.h>
#include <lib/kb4/ui/realtimeqcp/colorsetter.h>

#include "abstractgraph.h"

namespace Ui {
class AbstractPlot;
}

class AbstractPlot : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractPlot(QWidget *parent = nullptr);
    ~AbstractPlot();




    QVector<AbstractGraph *> graphs() const;

    QCustomPlot *qcp() const;

private slots:
    void on_pushButtonPrintScreen_clicked();

    void on_pushButtonHelp_clicked();

private:
    Ui::AbstractPlot *ui;
    void configureLegend();
    QVector<AbstractGraph *> _graphs;

protected:
    const QString timeLabel = tr("Время");

    virtual void configurePlot() = 0;
    AbstractGraph* addGraph(AbstractGraph *graph);
    ColorSetter colorSetter;

    QCustomPlot *_plot;
    QVBoxLayout *legendLayout;
    QLabel *labelTime;

};

#endif // ABSTRACTPLOT_H
