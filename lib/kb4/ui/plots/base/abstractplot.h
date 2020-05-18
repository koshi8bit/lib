#ifndef ABSTRACTPLOT_H
#define ABSTRACTPLOT_H

#include <QWidget>
#include <lib/kb4/ui/qcustomplot/qcustomplot.h>

#include <lib/kb4/ui/printscreener/printscreener.h>

#include "abstractgraph.h"
#include "colorsetter.h"
#include "axisvalueconfig.h"

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

    //TODO delete method
    void configureAxis(bool yAxis2, const QString &label, const QString &postfix = "", double min=0, double max=100, int precision = 0, QCPAxis::ScaleType scaleType = QCPAxis::stLinear);
    void configureAxis(QCPAxis *axis, const QString &label, const QString &postfix = "", double min=0, double max=100, int precision = 0, QCPAxis::ScaleType scaleType = QCPAxis::stLinear);


private slots:
    void axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);
    void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);

    void on_pushButtonPrintScreen_clicked();

    void on_pushButtonHelp_clicked();

    void on_pushButtonOptions_toggled(bool checked);

    void on_pushButtonPrintScreenCopy_clicked();

    void on_pushButtonPrintScreenPaint_clicked();

private:
    Ui::AbstractPlot *ui;
    void configureLegend();
    void autoScaleAxis(QCPAxis *axis);

    void setButtonsVisible(bool visible, bool options);

    void setAxisType(QCPAxis *axis, QCPAxis::ScaleType scaleType);

protected:
    ColorSetter colorSetter;

    void configurePlotBackground(bool excelStyle);
    void configurePlotBackgroundAxis(QCPAxis *axis, bool excelStyle);

    virtual void abstractAxisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event);


    QCustomPlot *_qcp;
    QVBoxLayout *_legendLayout;
    QVector<AbstractGraph *> _graphs;


};

#endif // ABSTRACTPLOT_H
