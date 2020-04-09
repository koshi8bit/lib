#ifndef PLOTWITHLEGEND_H
#define PLOTWITHLEGEND_H

#include <QWidget>

#include <lib/qcustomplot/qcustomplot.h>
#include <lib/kb4/ui/printscreener/printscreener.h>

namespace Ui {
class PlotWithLegend;
}

class QcpWithLegend : public QWidget
{
    Q_OBJECT

public:
    explicit QcpWithLegend(QWidget *parent = nullptr);
    ~QcpWithLegend();

private slots:
    void on_pushButtonPrintScreen_clicked();

    void on_pushButtonHelp_clicked();

private:
    Ui::PlotWithLegend *ui;
    void configureLegend();

protected:
    const QString timeLabel = tr("Время");

    virtual void configurePlot() = 0;

    QCustomPlot *plot;
    QVBoxLayout *legendLayout;
    QLabel *labelTime;

};

#endif // PLOTWITHLEGEND_H
