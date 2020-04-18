#include "abstractplot.h"
#include "ui_abstractplot.h"

AbstractPlot::AbstractPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbstractPlot)
{
    ui->setupUi(this);
    ui->widgetToolTip->setVisible(false);
    configureLegend();

    _plot = ui->plot;

}

AbstractPlot::~AbstractPlot()
{
    delete ui;
}

AbstractGraph *AbstractPlot::addGraph(AbstractGraph *graph)
{
    _graphs.append(graph);
    legendLayout->insertWidget(legendLayout->count()-1, graph->legendItem());
    return graph;
}


QVector<AbstractGraph *> AbstractPlot::graphs() const
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

    labelTime = new QLabel(this);
    labelTime->setText(timeLabel);
    legendLayout->addWidget(labelTime);

    auto spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    legendLayout->addItem(spacer);
}

QCustomPlot *AbstractPlot::qcp() const
{
    return _plot;
}
