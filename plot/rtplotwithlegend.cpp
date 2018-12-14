#include "rtplotwithlegend.h"
#include "ui_rtplotwithlegend.h"

RTPlotWithLegend::RTPlotWithLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RTPlotWithLegend)
{
    ui->setupUi(this);

    auto plot = ui->plot;
}

RTPlotWithLegend::~RTPlotWithLegend()
{
    delete ui;
}

void RTPlotWithLegend::setMarginGroup(QCPMarginGroup *mg)
{
    ui->plot->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, mg);
}
