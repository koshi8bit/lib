#ifndef GRADIENTLINEEDITWIDGET_H
#define GRADIENTLINEEDITWIDGET_H

#include <QWidget>

#include <lib/qcustomplot/qcustomplot.h>

namespace Ui {
class GradientLineEditWidget;
}

class GradientLineEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GradientLineEditWidget(QWidget *parent = nullptr);
    ~GradientLineEditWidget();

signals:
    void rangeChanged(QCPRange range);

private slots:
    void on_doubleSpinBoxMin_valueChanged(double arg1);
    void on_doubleSpinBoxMax_valueChanged(double arg1);

private:
    Ui::GradientLineEditWidget *ui;
};

#endif // GRADIENTLINEEDITWIDGET_H
