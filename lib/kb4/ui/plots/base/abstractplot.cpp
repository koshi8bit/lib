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
    connect(qcp(), &QCustomPlot::axisClick, this, &AbstractPlot::axisClick);
    connect(qcp(), &QCustomPlot::axisDoubleClick, this, &AbstractPlot::axisDoubleClick);

    ui->splitter->setStretchFactor(0, 5);
    ui->splitter->setStretchFactor(1, 1);

    ui->splitter->widget(1)->setMinimumWidth(200);
    ui->splitter->widget(1)->setMaximumWidth(200);

    setButtonsVisible(false, false);

}

AbstractPlot::~AbstractPlot()
{
    delete ui;
}

void AbstractPlot::axisClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    Q_UNUSED(part)
    if (event->button() == Qt::MouseButton::RightButton)
    {
        autoScaleAxis(axis);
        qcp()->replot();
    }
}

void AbstractPlot::axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    abstractAxisDoubleClick(axis, part, event);
}

void AbstractPlot::autoScaleAxis(QCPAxis *axis)
{
    axis->rescale(true);
    auto delta = (axis->range().upper - axis->range().lower)*0.05; // 5%
    axis->setRange(axis->range().lower - delta, axis->range().upper + delta);
}

void AbstractPlot::setButtonsVisible(bool visible, bool options)
{
    ui->pushButtonHelp->setVisible(visible);
    ui->pushButtonPrintScreen->setVisible(visible);
    ui->pushButtonPrintScreenCopy->setVisible(visible);
    ui->pushButtonPrintScreenPaint->setVisible(visible);

    if (options)
        ui->pushButtonOptions->setVisible(visible);
}

void AbstractPlot::addAbstractGraph(AbstractGraph *graph)
{
    _graphs.append(graph);
    _legendLayout->insertWidget(_legendLayout->count()-1, graph->legendItem());
}

void AbstractPlot::setLegendVisible(bool visible)
{
    ui->scrollAreaLegend->setVisible(visible);
}


QVector<AbstractGraph *> AbstractPlot::graphs()
{
    return _graphs;
}

void AbstractPlot::on_pushButtonPrintScreen_clicked()
{
    setButtonsVisible(false, true);
    PrintScreener::save(this);
    setButtonsVisible(true, true);
}

void AbstractPlot::on_pushButtonHelp_clicked()
{
    QMessageBox::about(this, "Help", ui->widgetToolTip->toolTip());
}

void AbstractPlot::configureLegend()
{
    _legendLayout = new QVBoxLayout(ui->scrollAreaLegend->widget());

    auto spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    _legendLayout->addItem(spacer);
}

void AbstractPlot::configurePlotBackground(bool excelStyle)
{
    configurePlotBackgroundAxis(qcp()->xAxis, excelStyle);
    configurePlotBackgroundAxis(qcp()->yAxis, excelStyle);
    configurePlotBackgroundAxis(qcp()->yAxis2, excelStyle);


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

void AbstractPlot::configurePlotBackgroundAxis(QCPAxis *axis, bool excelStyle)
{
    axis->setLabelColor(Qt::white);
    axis->setBasePen(QPen(Qt::white, 1));
    axis->setSubTickPen(QPen(Qt::white, 1));
    axis->setTickLabelColor(Qt::white);
    axis->setTickPen(QPen(Qt::white, 1));
    if (excelStyle)
    {
        axis->grid()->setPen(QPen(QColor(80, 80, 80), 1, Qt::SolidLine));
    }
    else
    {
        axis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
        axis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
        axis->grid()->setSubGridVisible(true);
    }
    axis->grid()->setZeroLinePen(Qt::NoPen);
}

void AbstractPlot::abstractAxisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{
    Q_UNUSED(part)
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        auto plot = static_cast<QCustomPlot *>(sender());
        AxisValueConfig ac(axis, this);
        //ac.setModal(true);
        ac.exec();
        plot->replot();
    }
}

QCustomPlot *AbstractPlot::qcp()
{
    return _qcp;
}

void AbstractPlot::on_pushButtonOptions_toggled(bool checked)
{
    setButtonsVisible(checked, false);
}

void AbstractPlot::on_pushButtonPrintScreenCopy_clicked()
{
    setButtonsVisible(false, true);
    PrintScreener::copy(this);
    setButtonsVisible(true, true);
    ui->pushButtonOptions->setChecked(false);
}

void AbstractPlot::on_pushButtonPrintScreenPaint_clicked()
{
    setButtonsVisible(false, true);
    auto path = PrintScreener::save(this, "", true);
    setButtonsVisible(true, true);
    ui->pushButtonOptions->setChecked(false);

    if (path.isEmpty())
        return;

    //QThread::msleep(100);

    QProcess process;
    process.setProgram("mspaint.exe");
    process.setArguments( { path.replace("/", "\\") } );
    process.startDetached();
}
