#ifndef PLOTWITHLEGEND_H
#define PLOTWITHLEGEND_H

#include <QWidget>

#include <lib/qcustomplot/qcustomplot.h>
#include <lib/kb4/ui/printscreener/printscreener.h>
#include <lib/kb4/ui/realtimeqcp/graph.h>
#include <lib/kb4/ui/realtimeqcp/colorsetter.h>

namespace Ui {
class AbstractPlot;
}

class AbstractPlot : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractPlot(QWidget *parent = nullptr);
    ~AbstractPlot();

    Graph* addGraph(const QString &label, const QString &postfix = "", int precision = 3, bool scientificNotation = false);
    Graph* addGraph(QCPAxis *axis, const QString &label, const QString &postfix = "", int precision = 3, bool scientificNotation = false);

    QVector<Graph *> graphs() const;

private slots:
    void on_pushButtonPrintScreen_clicked();

    void on_pushButtonHelp_clicked();

private:
    Ui::AbstractPlot *ui;
    void configureLegend();
    ColorSetter colorSetter;
    QVector<Graph *> _graphs;

protected:
    const QString timeLabel = tr("Время");

    virtual void configurePlot() = 0;

    QCustomPlot *plot;
    QVBoxLayout *legendLayout;
    QLabel *labelTime;

};

#endif // PLOTWITHLEGEND_H
