#include "axisconfig.h"
#include "ui_axisconfig.h"

AxisConfig::AxisConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AxisConfig)
{
    ui->setupUi(this);
}

AxisConfig::~AxisConfig()
{
    delete ui;
}
