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

    ui->valuedoubleTest->configure("Ток", EasyLiving::postfixMilliAmpere());
    ui->valuedoubleTest->setValue(8.7);

    ui->valuedoubleTest_2->configure("Ток", EasyLiving::postfixMilliAmpere(), 1, false, true);
    ui->valuedoubleTest_2->setValue(8.7);


    connect(ui->valuedoubleTest_2, &ValueDouble::valueChanged, ui->valuedoubleTest_2, &ValueDouble::setValue);
    connect(ui->valuedoubleTest_2, &ValueDouble::valueChanged, [](double a) { qDebug() << a; });



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

    b = new ChannelDouble("BBB", EasyLiving::postfixMilli() + EasyLiving::postfixAmpere(), &(QStringList() << "b/middle2"), this);
    connect(ui->dialB, &QDial::valueChanged, b, &ChannelDouble::setValue);
    excelLog->addChannel(b);

    c = new ChannelDouble("CCC", EasyLiving::postfixKilo() + EasyLiving::postfixVolt(), &(QStringList() << "c/middle3"), this);
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
    graphHighVoltageElvFull = ui->rtPlotHighVoltageCurrent->addGraph(RTPlotWithLegend::Axis::yAxisL, "ЭЛВ (полное напряжение)", EasyLiving::postfixKilo() + EasyLiving::postfixVolt());
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
    RealTimeQCP * plot;
    mg = new QCPMarginGroup(ui->rtPlotHighVoltageCurrent->plot());

    plot = ui->realTimeQCPU;
    plot->configureAxis(plot->plot()->yAxis, tr("Напруга"), EasyLiving::postfixVolt(), 0, 2300);
    configureRealTimeQCPPlot(plot);

    plot = ui->realTimeQCPI;
    plot->configureAxis(plot->plot()->yAxis, tr("Тоооок"), EasyLiving::postfixMilliAmpere(), 0, 10);
    configureRealTimeQCPPlot(plot);

    plot = ui->realTimeQCPTemperature;
    plot->configureAxis(plot->plot()->yAxis, tr("Температурим"), EasyLiving::postfixCelsius(), 0, 200);
    configureRealTimeQCPPlot(plot);

    plot = ui->realTimeQCPPower;
    plot->configureAxis(plot->plot()->yAxis, tr("МОООЩА!"), EasyLiving::postfixWatt(), 0, 700);
    configureRealTimeQCPPlot(plot);

    plot = ui->realTimeQCPPersent;
    plot->configureAxis(plot->plot()->yAxis, tr("Процентики"), EasyLiving::postfixPersent(), 0, 100);
    configureRealTimeQCPPlot(plot);

    plot = ui->realTimeQCPBool;
    plot->configureAxis(plot->plot()->yAxis, tr("True/False"), "", -0.2, 1.2);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTick(0, "False");
    textTicker->addTick(1, "True");
    plot->plot()->yAxis->setTicker(textTicker);
    //plot->plot()->yAxis->setSubTicks(false);
    configureRealTimeQCPPlot(plot);

    plot = ui->realTimeQCPVacuum;
    plot->configureAxis(plot->plot()->yAxis, tr("Вакуум"), "Pa", 1.0e-04, 1.0e+01, QCPAxis::stLogarithmic);
    configureRealTimeQCPPlot(plot);

    plot = ui->realTimeQCPRadiation;
    plot->configureAxis(plot->plot()->yAxis, tr("Радиашн"), EasyLiving::postfixSievertPerHour(), 1.0e-07, 1.0e-01, QCPAxis::stLogarithmic);
    configureRealTimeQCPPlot(plot);
}

void MainWindow::configureRealTimeQCPPlot(RealTimeQCP *plot)
{
    plot->setMarginGroup(mg);

    connect(plot->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(realTimeQCPChangeRange(QCPRange)));
    connect(plot->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(realTimeQCPMouseMove(QMouseEvent*)));
    connect(plot, &RealTimeQCP::realTimeChanged, this, &MainWindow::realTimeQCPRealTimeChanged);
    connect(plot, &RealTimeQCP::moveLineRealTimeChanged, this, &MainWindow::realTimeQCPMoveLineRealTimeChanged);
}


void MainWindow::on_checkBoxRealTime_stateChanged(int arg1)
{
    plotUpdateRealTIme = static_cast<bool>(arg1);

    ui->rtPlotHighVoltageCurrent->setRealTime(plotUpdateRealTIme);
    ui->rtPlotTemperaturePower->setRealTime(plotUpdateRealTIme);
    ui->rtPlotVacuumRadiation->setRealTime(plotUpdateRealTIme);
}



////////////////////////////////


void MainWindow::realTimeQCPChangeRangeCheckAxis(QCPAxis *axis, RTPlotWithLegend *plot, QCPRange range)
{
    if (axis != plot->plot()->xAxis)
        plot->plot()->xAxis->setRange(range);
}

void MainWindow::plotChangeRange(QCPRange range)
{
    QCPAxis* axis = static_cast<QCPAxis *>(QObject::sender());

    realTimeQCPChangeRangeCheckAxis(axis, ui->rtPlotHighVoltageCurrent, range);
    realTimeQCPChangeRangeCheckAxis(axis, ui->rtPlotTemperaturePower, range);
    realTimeQCPChangeRangeCheckAxis(axis, ui->rtPlotVacuumRadiation, range);

//    if (axis != ui->rtPlotHighVoltageCurrent->plot()->xAxis)
//        ui->rtPlotHighVoltageCurrent->plot()->xAxis->setRange(range);
//    if (axis != ui->rtPlotTemperaturePower->plot()->xAxis)
//        ui->rtPlotTemperaturePower->plot()->xAxis->setRange(range);
//    if (axis != ui->rtPlotVacuumRadiation->plot()->xAxis)
//        ui->rtPlotVacuumRadiation->plot()->xAxis->setRange(range);

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


void MainWindow::realTimeQCPChangeRangeCheckAxis(RealTimeQCP *plot, QCPAxis *axis, QCPRange range)
{
    if (axis != plot->plot()->xAxis)
        plot->plot()->xAxis->setRange(range);
}

void MainWindow::realTimeQCPChangeRange(QCPRange range)
{
    QCPAxis* axis = static_cast<QCPAxis *>(QObject::sender());

    realTimeQCPChangeRangeCheckAxis(ui->realTimeQCPU, axis, range);
    realTimeQCPChangeRangeCheckAxis(ui->realTimeQCPI, axis, range);
    realTimeQCPChangeRangeCheckAxis(ui->realTimeQCPU, axis, range);

    ui->rtPlotHighVoltageCurrent->plot()->replot();
}

void MainWindow::realTimeQCPMouseMove(QMouseEvent *event)
{

}

void MainWindow::realTimeQCPRealTimeChanged(bool newValue)
{

}

void MainWindow::realTimeQCPMoveLineRealTimeChanged(bool newValue)
{

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
