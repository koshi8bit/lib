#include "minmaxwidget.h"
#include "ui_minmaxwidget.h"

MinMaxWidget::MinMaxWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinMaxWidget)
{
    ui->setupUi(this);
}

MinMaxWidget::~MinMaxWidget()
{
    delete ui;
}

void MinMaxWidget::on_doubleSpinBoxMin_valueChanged(double arg1)
{
    emit rangeChanged(arg1, ui->doubleSpinBoxMax->value());
}

void MinMaxWidget::on_doubleSpinBoxMax_valueChanged(double arg1)
{
    emit rangeChanged(ui->doubleSpinBoxMax->value(), arg1);
}
