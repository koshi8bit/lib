#include "mainwindow.h"
#include "ui_mainwindow.h"






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new QSettings("settings.ini", QSettings::IniFormat, this);

    if(settings->value("qDebug/saveToFile", false).toBool())
        configureQDebug();

    configureRealTimeQCP();
    configureRTPlotWithLegend();
    configureGraphs();

    configureTimers();

    configureGradientLineEdit();

    configureExcelLog();

    configureWorker();

    ui->valuedoubleTest->configure("Ток", EasyLiving::postfixMilliAmpereRu());
    ui->valuedoubleTest->setValue(8.7);

    ui->valuedoubleTest_2->configure("Ток", EasyLiving::postfixMilliAmpereRu(), 1, false, true);
    ui->valuedoubleTest_2->setValue(8.7);


    connect(ui->valuedoubleTest_2, &ValueDouble::valueChanged, ui->valuedoubleTest_2, &ValueDouble::setValue);
    connect(ui->valuedoubleTest_2, &ValueDouble::valueChanged, [this](double a) { qDebug() << a; });



    eh.checkForErrors();

//    auto a = QLocale(QLocale::Russian);
//    qDebug() << "Разделитель тчк/зпт" << a.decimalPoint();
//    qDebug() << "Разделитель группы" << QString(a.groupSeparator());
//    qDebug() << QString::number(1300.2, 'f', 2);

//    QTime t1(15, 23, 16);
//    QTime t2(12, 11, 02);

//    qDebug() << t2.secsTo(t1);
//    QTime t3 = QTime(0, 0, 0).addSecs(t2.secsTo(t1));

//    qDebug() << t3;

}


void MainWindow::configureExcelLog()
{
    ///////
    excelLog = new TimeLog();
    connect(excelLog, &TimeLog::errorOcurred, &eh, &ErrorHandler::processError);
    excelLog->configure("./Log", Excel::LogName | Excel::WidgetName);
    ///////


    a = new ChannelDouble("AAA", EasyLiving::postfixCelsius(), &(QStringList() << "a/middle1"), this);
    connect(ui->dialA, &QDial::valueChanged, a, &ChannelDouble::setValue);
    excelLog->addChannel(a);

    b = new ChannelDouble("BBB", EasyLiving::postfixMilliRu() + EasyLiving::postfixAmpereRu(), &(QStringList() << "b/middle2"), this);
    connect(ui->dialB, &QDial::valueChanged, b, &ChannelDouble::setValue);
    excelLog->addChannel(b);

    c = new ChannelDouble("CCC", EasyLiving::postfixKiloRu() + EasyLiving::postfixVoltRu(), &(QStringList() << "c/middle3"), this);
    //FIXME tima45
    //connect(ui->doubleSpinBoxC, &QDoubleSpinBox::valueChanged, c, &ChannelDouble::setValue);
    connect(ui->doubleSpinBoxC, SIGNAL(valueChanged(double)), c, SLOT(setValue(double)));
    c->setValue(3.009);
    excelLog->addChannel(c);

    excelLog->finishConfigure();





}

void MainWindow::configureWorker()
{
    w = new Worker("test", this);
    w->heavyWork = [this]() { this->heavyWork();};
    w->start();
}

void MainWindow::heavyWork()
{
    qDebug() << "heavyWork";
}

void MainWindow::configureTimers()
{
    timerAddData1 = new QTimer(this);
    timerAddData1->setInterval(addData1MSEC);
    connect(timerAddData1, SIGNAL(timeout()), this, SLOT(addData1()));
    timerAddData1->start();

    timerAddData2 = new QTimer(this);
    timerAddData2->setInterval(addData2MSEC);
    connect(timerAddData2, SIGNAL(timeout()), this, SLOT(addData2()));
    timerAddData2->start();

    timerReplot = new QTimer(this);
    timerReplot->setInterval(plotUpdateIntervalMSEC);
    connect(timerReplot, SIGNAL(timeout()), this, SLOT(plotReplotTimeout()));
    timerReplot->start();
}

void MainWindow::configureGradientLineEdit()
{
    //TODO
    //connect(ui->gradientLineEdit, &GradientLineEdit::rangeChanged, ui->minMax, &MinMax::setRange);
    ui->gradientLineEdit->configure();
    ui->gradientLineEdit->setMinMax(20, 50);
    ui->minMax->setRange(ui->gradientLineEdit->min(), ui->gradientLineEdit->max());
    connect(ui->minMax, &MinMax::rangeChanged, this, &MainWindow::gradientLineEdit_rangeChanged);
}

void MainWindow::configurePlot(RTPlotWithLegend *rtPlot, QString yAxisLabel, double yAxisMin, double yAxisMax, QCPAxis::ScaleType yAxisScaleType, QString yAxis2Label, double yAxis2Min, double yAxis2Max, QCPAxis::ScaleType yAxis2ScaleType)
{
    rtPlot->configureAxis(RTPlotWithLegend::Axis::yAxisL, yAxisLabel, yAxisMin, yAxisMax, yAxisScaleType);
    rtPlot->configureAxis(RTPlotWithLegend::Axis::yAxisR, yAxis2Label, yAxis2Min, yAxis2Max, yAxis2ScaleType);
    rtPlot->setMarginGroup(mg);
    connect(rtPlot->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(plotChangeRange(QCPRange)));
    connect(rtPlot->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(plotMouseMove(QMouseEvent*)));
    connect(rtPlot, &RTPlotWithLegend::realTimeChanged, this, &MainWindow::plotRealTimeChanged);
    connect(rtPlot, &RTPlotWithLegend::moveLineRealTimeChanged, this, &MainWindow::plotMoveLineRealTimeChanged);
}

void MainWindow::configureRTPlotWithLegend()
{
    mg = new QCPMarginGroup(ui->rtPlotHighVoltageCurrent->plot());

    configurePlot(ui->rtPlotHighVoltageCurrent, "Энергия (кВ)", 0, 1250, QCPAxis::ScaleType::stLinear, "Ток (мА)", 0, 10, QCPAxis::ScaleType::stLinear);
    ui->rtPlotHighVoltageCurrent->setNumberPrecision(RTPlotWithLegend::Axis::yAxisR, 2);

    connect(ui->rtPlotHighVoltageCurrent->plot(), SIGNAL(afterReplot()), ui->rtPlotTemperaturePower->plot(), SLOT(replot()));
    connect(ui->rtPlotHighVoltageCurrent->plot(), SIGNAL(afterReplot()), ui->rtPlotVacuumRadiation->plot(), SLOT(replot()));
    connect(ui->rtPlotHighVoltageCurrent, &RTPlotWithLegend::lineRealTimeMoved, this, &MainWindow::plotLineRealTimeMoved);

    configurePlot(ui->rtPlotTemperaturePower, "Температура (С)", 10, 180, QCPAxis::ScaleType::stLinear, "Мощность (Вт)", 0, 700, QCPAxis::ScaleType::stLinear);
    ui->rtPlotTemperaturePower->setLabelTimeVisible(false);

    configurePlot(ui->rtPlotVacuumRadiation, "Вакуум (Пa)", 1.0e-5, 1, QCPAxis::ScaleType::stLogarithmic, "Радиация (Зв)", 1.0e-5, 1, QCPAxis::ScaleType::stLogarithmic);
    ui->rtPlotVacuumRadiation->setLabelTimeVisible(false);
}




void MainWindow::addData1()
{
    graphHighVoltageElvFull->addData(now, sin(5.0f/2*cos(now)));
    graphTemperaturePyrometer->addData(now, sin(9.0f/2*cos(now)));


}

void MainWindow::addData2()
{
    graphCurrentBergozHebt->addData(now, QRandomGenerator::global()->bounded(1.0));
    graphHighVoltageElvFirstSection->addData(now, sin(now));
    graphVacuumTandem->addData(now, qPow(qSin(now), 2) - 2*qSin(now) - 2);

}

//FIXME tima45 diff?
//void MainWindow::replot()
//{
//    auto now = RTPlotWithLegend::now();
//    auto rtPlot = ui->rtPlotHighVoltageCurrent;

//    if (rtPlot->realTime())
//    {
//        rtPlot->plot()->xAxis->setRange(
//                    now - rtPlot->timeAxisRangeSEC(),
//                    now);
//    }

//    rtPlot->plot()->replot();
//}

void MainWindow::plotReplotTimeout()
{
    now = RTPlotWithLegend::now();

    if (ui->rtPlotHighVoltageCurrent->realTime())
    {
        ui->rtPlotHighVoltageCurrent->plot()->xAxis->setRange(now - ui->rtPlotHighVoltageCurrent->timeAxisRangeSEC(), now);
    }

    ui->rtPlotHighVoltageCurrent->plot()->replot();
}

void MainWindow::plotLineRealTimeMoved()
{
    auto message = QString("%1").arg(graphHighVoltageElvFull->value());
    this->setWindowTitle(message);
}



void MainWindow::configureGraphs()
{
    configureGraphsEnergyCurrent();
    configureGraphsTemperaturePower();
    configureGraphsVacuumRadiation();
}

void MainWindow::configureGraphsEnergyCurrent()
{
    graphHighVoltageElvFull = ui->rtPlotHighVoltageCurrent->addGraph(RTPlotWithLegend::Axis::yAxisL, "ЭЛВ (полное напряжение)", EasyLiving::postfixKiloRu() + EasyLiving::postfixVoltRu());
    graphHighVoltageElvFirstSection = ui->rtPlotHighVoltageCurrent->addGraph(RTPlotWithLegend::Axis::yAxisL, "ЭЛВ (первая секция)");
    graphHighVoltageElvFirstSection->setVisible(false);
    graphHighVoltageElvFirstSection->setColor(QColor("#BBBBBB"));
    graphCurrentBergozHebt = ui->rtPlotHighVoltageCurrent->addGraph(RTPlotWithLegend::Axis::yAxisR, "Bergoz (выс. эн. тракт)");
}

void MainWindow::configureGraphsTemperaturePower()
{
    graphTemperaturePyrometer = ui->rtPlotTemperaturePower->addGraph(RTPlotWithLegend::Axis::yAxisL, "Пирометр");
}

void MainWindow::configureGraphsVacuumRadiation()
{
    graphVacuumTandem = ui->rtPlotVacuumRadiation->addGraph(RTPlotWithLegend::Axis::yAxisL, "Тандем");
}




MainWindow::~MainWindow()
{
    timerAddData1->stop();
    delete timerAddData1;

    timerAddData2->stop();
    delete timerAddData2;

    timerReplot->stop();
    delete timerReplot;

    delete excelLog;

    delete a;
    delete b;


    delete ui;
    delete mg;//->deleteLater();
}

void MainWindow::configureRealTimeQCP()
{
    auto plot = ui->realTimeQCPU;
    //plot->configureAxis(plot->plot()->yAxis, tr("Напруга"), 0, 2300, QCPAxis::stLinear, 0);
    plot->configureAxis(plot->plot()->yAxis, tr("Напруга"), 0, 2300);
    plot->configureAxis(plot->plot()->yAxis2, tr("Напруга2"), 0, 500);
}


void MainWindow::on_checkBoxRealTime_stateChanged(int arg1)
{
    plotUpdateRealTIme = static_cast<bool>(arg1);

    ui->rtPlotHighVoltageCurrent->setRealTime(plotUpdateRealTIme);
    ui->rtPlotTemperaturePower->setRealTime(plotUpdateRealTIme);
    ui->rtPlotVacuumRadiation->setRealTime(plotUpdateRealTIme);
}


////////////////////////////////

void MainWindow::plotChangeRange(QCPRange range)
{
    QCPAxis* axis = static_cast<QCPAxis *>(QObject::sender());

    if (axis != ui->rtPlotHighVoltageCurrent->plot()->xAxis)
        ui->rtPlotHighVoltageCurrent->plot()->xAxis->setRange(range);
    if (axis != ui->rtPlotTemperaturePower->plot()->xAxis)
        ui->rtPlotTemperaturePower->plot()->xAxis->setRange(range);
    if (axis != ui->rtPlotVacuumRadiation->plot()->xAxis)
        ui->rtPlotVacuumRadiation->plot()->xAxis->setRange(range);

    ui->rtPlotHighVoltageCurrent->plot()->replot();
}

void MainWindow::plotMouseMove(QMouseEvent *event)
{
    auto plot = static_cast<QCustomPlot*>(sender());
    auto time = plot->xAxis->pixelToCoord(event->x());

    if (plot != ui->rtPlotHighVoltageCurrent->plot())
        ui->rtPlotHighVoltageCurrent->mouseMove(time);
    if (plot != ui->rtPlotTemperaturePower->plot())
        ui->rtPlotTemperaturePower->mouseMove(time);
    if (plot != ui->rtPlotVacuumRadiation->plot())
        ui->rtPlotVacuumRadiation->mouseMove(time);

    ui->rtPlotHighVoltageCurrent->plot()->replot();
}

void MainWindow::plotRealTimeChanged(bool newValue)
{
    ui->checkBoxRealTime->setChecked(newValue);
    auto plot = static_cast<RTPlotWithLegend *>(sender());

    if (plot != ui->rtPlotHighVoltageCurrent)
        ui->rtPlotHighVoltageCurrent->setRealTime(newValue);
    if (plot != ui->rtPlotTemperaturePower)
        ui->rtPlotTemperaturePower->setRealTime(newValue);
    if (plot != ui->rtPlotVacuumRadiation)
        ui->rtPlotVacuumRadiation->setRealTime(newValue);
}

void MainWindow::plotMoveLineRealTimeChanged(bool newValue)
{
    auto plot = static_cast<RTPlotWithLegend *>(sender());

    if (plot != ui->rtPlotHighVoltageCurrent)
        ui->rtPlotHighVoltageCurrent->setMoveLineRealTime(newValue);
    if (plot != ui->rtPlotTemperaturePower)
        ui->rtPlotTemperaturePower->setMoveLineRealTime(newValue);
    if (plot != ui->rtPlotVacuumRadiation)
        ui->rtPlotVacuumRadiation->setMoveLineRealTime(newValue);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->gradientLineEdit->display(value);
}

void MainWindow::gradientLineEdit_rangeChanged(double min, double max)
{
    ui->gradientLineEdit->setMinMax(min, max);
}

void MainWindow::on_pushButtonLogCommit_clicked()
{
    excelLog->commit();
}

void MainWindow::on_pushButtonLogPush_clicked()
{
    excelLog->push();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    excelLog->setAutoLog(arg1 == 2);
}

void MainWindow::on_pushButton_clicked()
{
    eh.processError("i wanna sleep");
}

void MainWindow::on_pushButtonExit_clicked()
{
    qDebug() << "lol";
}
