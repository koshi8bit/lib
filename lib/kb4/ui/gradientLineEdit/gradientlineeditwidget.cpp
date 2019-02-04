#include "gradientlineeditwidget.h"
#include "ui_gradientlineeditwidget.h"

GradientLineEditWidget::GradientLineEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GradientLineEditWidget)
{
    ui->setupUi(this);
}

GradientLineEditWidget::~GradientLineEditWidget()
{
    delete ui;
}

void GradientLineEditWidget::on_doubleSpinBoxMin_valueChanged(double arg1)
{
    emit rangeChanged(QCPRange(arg1, ui->doubleSpinBoxMax->value()));
}

void GradientLineEditWidget::on_doubleSpinBoxMax_valueChanged(double arg1)
{
    emit rangeChanged(QCPRange(ui->doubleSpinBoxMax->value(), arg1));
}
