#include "qcpwithlegend.h"
#include "ui_plotwithlegend.h"

QcpWithLegend::QcpWithLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotWithLegend)
{
    ui->setupUi(this);
    ui->widgetToolTip->setVisible(false);
    configureLegend();

    plot = ui->plot;

}

QcpWithLegend::~QcpWithLegend()
{
    delete ui;
}

void QcpWithLegend::on_pushButtonPrintScreen_clicked()
{
    PrintScreener::save(this);
}

void QcpWithLegend::on_pushButtonHelp_clicked()
{
    QMessageBox::about(this, "Help", ui->widgetToolTip->toolTip());
}

void QcpWithLegend::configureLegend()
{
    legendLayout = new QVBoxLayout(ui->scrollAreaLegend->widget());

    labelTime = new QLabel(this);
    labelTime->setText(timeLabel);
    legendLayout->addWidget(labelTime);

    auto spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    legendLayout->addItem(spacer);
}
