#include "abstractplot.h"
#include "ui_abstractplot.h"

AbstractPlot::AbstractPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbstractPlot)
{
    ui->setupUi(this);
    ui->widgetToolTip->setVisible(false);
    configureLegend();

    _qcp = ui->plot;

    ui->splitter->setStretchFactor(0, 5);
    ui->splitter->setStretchFactor(1, 1);

    ui->splitter->widget(1)->setMinimumWidth(200);
    ui->splitter->widget(1)->setMaximumWidth(200);

}

AbstractPlot::~AbstractPlot()
{
    delete ui;
}

void AbstractPlot::addAbstractGraph(AbstractGraph *graph)
{
    _graphs.append(graph);
    legendLayout->insertWidget(legendLayout->count()-1, graph->legendItem());
}


QVector<AbstractGraph *> AbstractPlot::graphs()
{
    return _graphs;
}

void AbstractPlot::on_pushButtonPrintScreen_clicked()
{
    PrintScreener::save(this);
}

void AbstractPlot::on_pushButtonHelp_clicked()
{
    QMessageBox::about(this, "Help", ui->widgetToolTip->toolTip());
}

void AbstractPlot::configureLegend()
{
    legendLayout = new QVBoxLayout(ui->scrollAreaLegend->widget());    

    auto spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    legendLayout->addItem(spacer);
}

void AbstractPlot::configurePlot()
{

}

void AbstractPlot::configurePlotBackground()
{
    configurePlotBackgroundAxis(qcp()->xAxis);
    configurePlotBackgroundAxis(qcp()->yAxis);
    configurePlotBackgroundAxis(qcp()->yAxis2);


    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    qcp()->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(60, 60, 60));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    qcp()->axisRect()->setBackground(axisRectGradient);
}

void AbstractPlot::configurePlotBackgroundAxis(QCPAxis *axis)
{
    axis->setLabelColor(Qt::white);
    axis->setBasePen(QPen(Qt::white, 1));
    axis->setSubTickPen(QPen(Qt::white, 1));
    axis->setTickLabelColor(Qt::white);
    axis->setTickPen(QPen(Qt::white, 1));
    axis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    axis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    axis->grid()->setSubGridVisible(true);
    axis->grid()->setZeroLinePen(Qt::NoPen);
}


QCustomPlot *AbstractPlot::qcp()
{
    return _qcp;
}
