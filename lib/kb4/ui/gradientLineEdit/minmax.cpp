#include "minmax.h"
#include "ui_minmax.h"

MinMax::MinMax(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinMax)
{
    ui->setupUi(this);
}

MinMax::~MinMax()
{
    delete ui;
}

void MinMax::setRange(double min, double max)
{
    ui->doubleSpinBoxMin->setValue(min);
    ui->doubleSpinBoxMax->setValue(max);
}

void MinMax::on_doubleSpinBoxMin_valueChanged(double arg1)
{
    emit rangeChanged(arg1, ui->doubleSpinBoxMax->value());
}

void MinMax::on_doubleSpinBoxMax_valueChanged(double arg1)
{
    emit rangeChanged(ui->doubleSpinBoxMin->value(), arg1);
}
