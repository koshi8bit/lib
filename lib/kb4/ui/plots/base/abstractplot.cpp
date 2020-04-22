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

QCustomPlot *AbstractPlot::qcp()
{
    return _qcp;
}
