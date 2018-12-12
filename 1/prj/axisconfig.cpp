#include "axisconfig.h"
#include "ui_axisconfig.h"

AxisConfig::AxisConfig(QCPAxis *axis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisConfig)
{
    ui->setupUi(this);


    this->axis = axis;
    ui->dateTimeEditMin->setVisible(false);
    ui->dateTimeEditMax->setVisible(false);

    ui->lineEditLabel->setText(axis->label());

}

AxisConfig::~AxisConfig()
{
    delete ui;
}

void AxisConfig::on_lineEditLabel_editingFinished()
{
    axis->setLabel(ui->lineEditLabel->text());
}
