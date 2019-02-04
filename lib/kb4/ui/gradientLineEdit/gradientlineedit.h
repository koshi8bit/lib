#ifndef GRADIENTLINEEDIT_H
#define GRADIENTLINEEDIT_H

#include <QObject>
#include <QLineEdit>

#include <lib/qcustomplot/qcustomplot.h>

class GradientLineEdit : public QLineEdit
{
public:
    GradientLineEdit(QWidget *parent);

    void configure();
    void configure(QCPRange *range, QCPColorGradient *gradient);
    void configureRange();
    void configureGradient();
    void setMinMax(double min, double max);
    void setRange(QCPRange *range, bool deleteOld = true);
    void setGradient(QCPColorGradient *gradient, bool deleteOld = true);

private:
    QCPRange *_range = nullptr;
    QCPColorGradient *_gradient = nullptr;

public slots:
    void display(double value);
};

#endif // GRADIENTLINEEDIT_H
