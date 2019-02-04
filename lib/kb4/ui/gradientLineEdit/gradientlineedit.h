#ifndef GRADIENTLINEEDIT_H
#define GRADIENTLINEEDIT_H

#include <QObject>
#include <QLineEdit>

#include <lib/qcustomplot/qcustomplot.h>

class GradientLineEdit : public QLineEdit
{
public:
    GradientLineEdit(QWidget *parent);

    void setMinMax(double min, double max);
    void setRange(QCPRange *range, bool deleteOld = true);
    void setColorGradient(QCPColorGradient *gradient, bool deleteOld = true);

private:
    QCPRange *_range;
    QCPColorGradient *_gradient;

public slots:
    void display(double value);
};

#endif // GRADIENTLINEEDIT_H
