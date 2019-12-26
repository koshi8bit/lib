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

    configureRealTimeQcpPlot();
    configureRealTimeQcpGraphs();

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
    excelLog->configure("./log", Excel::LogName | Excel::WidgetName);
    ///////


    a = new ChannelDouble("AAA", EasyLiving::postfixCelsius(), this);
    connect(ui->dialA, &QDial::valueChanged, a, &ChannelDouble::setValue);
    a->addGraphToPlot(ui->realTimeQCPPower);
    excelLog->addChannel(a);

    b = new ChannelDouble("BBB", EasyLiving::postfixMilli() + EasyLiving::postfixAmpere(), QStringList() << "b/middle2", this);
    connect(ui->dialB, &QDial::valueChanged, b, &ChannelDouble::setValue);
    excelLog->addChannel(b);

    c = new ChannelDouble("ЭЛВ/EnergyU get", this);
    //FIXME !tima45!
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

//    timerReplot = new QTimer(this);
//    timerReplot->setInterval(plotUpdateIntervalMSEC);
//    connect(timerReplot, SIGNAL(timeout()), this, SLOT(plotReplotTimeout()));
//    timerReplot->start();

    timerRealTimeQCPReplot = new QTimer(this);
    timerRealTimeQCPReplot->setInterval(plotUpdateIntervalMSEC);
    //connect(timerRealTimeQCPReplot, SIGNAL(timeout()), this, SLOT(timerRealTimeQCPReplotTimeout()));
    connect(timerRealTimeQCPReplot, &QTimer::timeout, ui->realTimeQCPU, &RealTimeQCP::moveTimeAxisRealTime);
    timerRealTimeQCPReplot->start();
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


void MainWindow::addData1()
{
    auto now = RealTimeQCP::currentDateTime();

    graphRealTimeQcpUa->addData(now, sin(5.0/2*cos(now)));
    graphRealTimeQcpIa->addData(now, sin(9.0/2*cos(now)));
}

void MainWindow::addData2()
{
    auto now = RealTimeQCP::currentDateTime();

    graphRealTimeQcpUb->addData(now, qPow(qSin(now), 2) - 2*qSin(now) - 2);
    graphRealTimeQcpBoola->addData(now, qrand() % 2);
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


void MainWindow::plotLineRealTimeMoved()
{
    auto message = QString("%1").arg(graphHighVoltageElvFull->value());
    this->setWindowTitle(message);
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

void MainWindow::configureRealTimeQcpPlot()
{
    mg = new QCPMarginGroup(ui->realTimeQCPU->plot());

    RealTimeQCP * plot;

    plot = ui->realTimeQCPU;
    plot->configureAxis(plot->plot()->yAxis, tr("Напруга"), EasyLiving::postfixVolt(), 0, 2300);
    configureRealTimeQcpPlot(plot);
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQCPI->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQCPTemperature->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQCPPower->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQCPPersent->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQCPBool->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQCPVacuum->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQCPRadiation->plot(), SLOT(replot()));

    plot = ui->realTimeQCPI;
    plot->configureAxis(plot->plot()->yAxis, tr("Тоооок"), EasyLiving::postfixMilliAmpere(), 0, 10, 2);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQCPTemperature;
    plot->configureAxis(plot->plot()->yAxis, tr("Температурим"), EasyLiving::postfixCelsius(), 0, 200);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQCPPower;
    plot->configureAxis(plot->plot()->yAxis, tr("МОООЩА!"), EasyLiving::postfixWatt(), 0, 700);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQCPPersent;
    plot->configureAxis(plot->plot()->yAxis, tr("Процентики"), EasyLiving::postfixPersent(), 0, 100);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQCPBool;
    plot->configureAxis(plot->plot()->yAxis, tr("True/False"), "", -0.2, 1.2);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTick(0, "False\nOff");
    textTicker->addTick(1, "True\nOn");
    plot->plot()->yAxis->setTicker(textTicker);
    //plot->plot()->yAxis->setSubTicks(false);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQCPVacuum;
    plot->configureAxis(plot->plot()->yAxis, tr("Вакуум"), "Pa", 1.0e-04, 1.0e+01, 0, QCPAxis::stLogarithmic);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQCPRadiation;
    plot->configureAxis(plot->plot()->yAxis, tr("Радиашн"), EasyLiving::postfixSievertPerHour(), 1.0e-07, 1.0e-01, 0, QCPAxis::stLogarithmic);
    configureRealTimeQcpPlot(plot);
}

void MainWindow::configureRealTimeQcpPlot(RealTimeQCP *plot)
{
    plot->setMarginGroup(mg);

    connect(plot->plot()->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(realTimeQCPChangeRange(QCPRange)));
    connect(plot->plot(), SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(realTimeQCPMouseMove(QMouseEvent*)));
    connect(plot, &RealTimeQCP::realTimeChanged, this, &MainWindow::realTimeQCPRealTimeChanged);
    connect(plot, &RealTimeQCP::moveLineRealTimeChanged, this, &MainWindow::realTimeQCPMoveLineRealTimeChanged);


}

void MainWindow::configureRealTimeQcpGraphs()
{
    graphRealTimeQcpUa = ui->realTimeQCPU->addGraph("ELV/E", EasyLiving::postfixVolt(), 2);
    graphRealTimeQcpUb = ui->realTimeQCPU->addGraph("Ultravolt/-300", EasyLiving::postfixVolt());

    graphRealTimeQcpIa = ui->realTimeQCPI->addGraph("Bergoz/Hebl", EasyLiving::postfixMilliAmpere(), 3);

    graphRealTimeQcpBoola = ui->realTimeQCPBool->addGraph("ЭЛВ/Напуск аргона", "", 0);
}


void MainWindow::on_checkBoxRealTime_stateChanged(int arg1)
{
    plotUpdateRealTIme = static_cast<bool>(arg1);
}



////////////////////////////////

void MainWindow::realTimeQCPChangeRangeCheckPlotAxis(RealTimeQCP *widget, QCPAxis *axis, QCPRange range)
{
    if (axis != widget->plot()->xAxis)
        widget->plot()->xAxis->setRange(range);
}

void MainWindow::realTimeQCPChangeRange(QCPRange range)
{
    QCPAxis* axis = static_cast<QCPAxis *>(QObject::sender());

    realTimeQCPChangeRangeCheckPlotAxis(ui->realTimeQCPU, axis, range);
    realTimeQCPChangeRangeCheckPlotAxis(ui->realTimeQCPI, axis, range);
    realTimeQCPChangeRangeCheckPlotAxis(ui->realTimeQCPTemperature, axis, range);
    realTimeQCPChangeRangeCheckPlotAxis(ui->realTimeQCPPower, axis, range);
    realTimeQCPChangeRangeCheckPlotAxis(ui->realTimeQCPPersent, axis, range);
    realTimeQCPChangeRangeCheckPlotAxis(ui->realTimeQCPBool, axis, range);
    realTimeQCPChangeRangeCheckPlotAxis(ui->realTimeQCPVacuum, axis, range);
    realTimeQCPChangeRangeCheckPlotAxis(ui->realTimeQCPRadiation, axis, range);

    ui->realTimeQCPU->plot()->replot();
}

void MainWindow::realTimeQCPMouseMoveCheckPlot(RealTimeQCP *widget, QCustomPlot *plot, double time)
{
    if (plot != widget->plot())
        widget->moveCursor(time);
}

void MainWindow::realTimeQCPMouseMove(QMouseEvent *event)
{
    auto plot = static_cast<QCustomPlot*>(sender());
    auto time = plot->xAxis->pixelToCoord(event->x());

    realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPU, plot, time);
    realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPI, plot, time);
    realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPTemperature, plot, time);
    realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPPower, plot, time);
    realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPPersent, plot, time);
    realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPBool, plot, time);
    realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPVacuum, plot, time);
    realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPRadiation, plot, time);

}

//realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPU,
//realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPI,
//realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPTemperature,
//realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPPower,
//realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPPersent,
//realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPBool,
//realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPVacuum,
//realTimeQCPMouseMoveCheckPlot(ui->realTimeQCPRadiation,

void MainWindow::realTimeQCPRealTimeChangedCheckWidget(RealTimeQCP *widget, RealTimeQCP *sender, bool newValue)
{
    if (sender != widget)
        widget->setRealTime(newValue);
}

void MainWindow::realTimeQCPRealTimeChanged(bool newValue)
{
    auto _sender = static_cast<RealTimeQCP *>(sender());

    realTimeQCPRealTimeChangedCheckWidget(ui->realTimeQCPU, _sender, newValue);
    realTimeQCPRealTimeChangedCheckWidget(ui->realTimeQCPI, _sender, newValue);
    realTimeQCPRealTimeChangedCheckWidget(ui->realTimeQCPTemperature, _sender, newValue);
    realTimeQCPRealTimeChangedCheckWidget(ui->realTimeQCPPower, _sender, newValue);
    realTimeQCPRealTimeChangedCheckWidget(ui->realTimeQCPPersent, _sender, newValue);
    realTimeQCPRealTimeChangedCheckWidget(ui->realTimeQCPBool, _sender, newValue);
    realTimeQCPRealTimeChangedCheckWidget(ui->realTimeQCPVacuum, _sender, newValue);
    realTimeQCPRealTimeChangedCheckWidget(ui->realTimeQCPRadiation, _sender, newValue);


}

void MainWindow::realTimeQCPMoveLineRealTimeChangedCheckWidget(RealTimeQCP *widget, RealTimeQCP *sender, bool newValue)
{
    if (sender != widget)
        widget->setMoveLineRealTime(newValue);
}

void MainWindow::realTimeQCPMoveLineRealTimeChanged(bool newValue)
{
    auto _sender = static_cast<RealTimeQCP *>(sender());

    realTimeQCPMoveLineRealTimeChangedCheckWidget(ui->realTimeQCPU, _sender, newValue);
    realTimeQCPMoveLineRealTimeChangedCheckWidget(ui->realTimeQCPI, _sender, newValue);
    realTimeQCPMoveLineRealTimeChangedCheckWidget(ui->realTimeQCPTemperature, _sender, newValue);
    realTimeQCPMoveLineRealTimeChangedCheckWidget(ui->realTimeQCPPower, _sender, newValue);
    realTimeQCPMoveLineRealTimeChangedCheckWidget(ui->realTimeQCPPersent, _sender, newValue);
    realTimeQCPMoveLineRealTimeChangedCheckWidget(ui->realTimeQCPBool, _sender, newValue);
    realTimeQCPMoveLineRealTimeChangedCheckWidget(ui->realTimeQCPVacuum, _sender, newValue);
    realTimeQCPMoveLineRealTimeChangedCheckWidget(ui->realTimeQCPRadiation, _sender, newValue);
}

void MainWindow::timerRealTimeQCPReplotTimeout()
{
    ui->realTimeQCPU->moveTimeAxisRealTime();
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

void MainWindow::on_pushButton_2_clicked()
{
    graphRealTimeQcpUa->setVisible(!graphRealTimeQcpUa->visible());
}
