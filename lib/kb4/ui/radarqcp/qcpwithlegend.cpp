#include "qcpwithlegend.h"
#include "ui_plotwithlegend.h"

QcpWithLegend::QcpWithLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QcpWithLegend)
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

Graph *QcpWithLegend::addGraph(const QString &label, const QString &postfix, int precision, bool scientificNotation)
{
    return addGraph(plot->yAxis, label, postfix, precision, scientificNotation);
}

Graph *QcpWithLegend::addGraph(QCPAxis *axis, const QString &label, const QString &postfix, int precision, bool scientificNotation)
{
    auto graph = new Graph( label,
                            postfix,
                            colorSetter.getColor(),
                            plot,
                            axis,
                            precision,
                            scientificNotation);

    _graphs.append(graph);
    legendLayout->insertWidget(legendLayout->count()-1, graph->graphLegendItem());
    return graph;
}

QVector<Graph *> QcpWithLegend::graphs() const
{
    return _graphs;
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
