#ifndef ABSTRACTPLOT_H
#define ABSTRACTPLOT_H

#include <QWidget>
#include <lib/kb4/ui/qcustomplot/qcustomplot.h>

#include <lib/kb4/ui/printscreener/printscreener.h>

#include "abstractgraph.h"
#include "colorsetter.h"

namespace Ui {
class AbstractPlot;
}

class AbstractPlot : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractPlot(QWidget *parent = nullptr);
    ~AbstractPlot();

    QVector<AbstractGraph *> graphs();
    void addAbstractGraph(AbstractGraph *graph);

    void setLegendVisible(bool visible);



//#define graphCast(element, type) static_cast<type>(element)
//    template < template <typename> class BinPred , typename T >
//    QVector<T*> foo()
//    {
//        QVector<T*> result;
//        foreach(auto element, graphs())
//        {
//            result.append(static_cast<T*>(element));
//        }
//        return result;
//    }

    QCustomPlot *qcp();

private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);

    void on_pushButtonPrintScreen_clicked();

    void on_pushButtonHelp_clicked();

private:
    Ui::AbstractPlot *ui;
    void configureLegend();
    void autoScaleAxis(QCPAxis *axis);

protected:
    virtual void configurePlot();
    ColorSetter colorSetter;

    void configurePlotBackground(bool excelStyle);
    void configurePlotBackgroundAxis(QCPAxis *axis, bool excelStyle);


    QCustomPlot *_qcp;
    QVBoxLayout *_legendLayout;
    QVector<AbstractGraph *> _graphs;


};

#endif // ABSTRACTPLOT_H
