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

void MinMax::on_doubleSpinBoxMin_valueChanged(double arg1)
{
    emit rangeChanged(arg1, ui->doubleSpinBoxMax->value());
}

void MinMax::on_doubleSpinBoxMax_valueChanged(double arg1)
{
    emit rangeChanged(ui->doubleSpinBoxMax->value(), arg1);
}
