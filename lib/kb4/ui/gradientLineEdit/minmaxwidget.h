#ifndef GRADIENTLINEEDITWIDGET_H
#define GRADIENTLINEEDITWIDGET_H

#include <QWidget>

#include <lib/qcustomplot/qcustomplot.h>

namespace Ui {
class MinMaxWidget;
}

class MinMaxWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MinMaxWidget(QWidget *parent = nullptr);
    ~MinMaxWidget();

signals:
    void rangeChanged(double min, double max);

private slots:
    void on_doubleSpinBoxMin_valueChanged(double arg1);
    void on_doubleSpinBoxMax_valueChanged(double arg1);

private:
    Ui::MinMaxWidget *ui;
};

#endif // GRADIENTLINEEDITWIDGET_H
