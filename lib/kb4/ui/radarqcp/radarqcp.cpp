#include "radarqcp.h"
#include "ui_radarqcp.h"

RadarQcp::RadarQcp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RadarQcp)
{
    ui->setupUi(this);
}

RadarQcp::~RadarQcp()
{
    delete ui;
}
