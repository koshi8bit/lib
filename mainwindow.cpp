#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(EasyLiving::formatWindowTitle("Tests"));

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

//    qDebug() << "writeFile" << EasyLiving::writeFile("D:/123-.txt", "sup bro\nsup buddy", false);
//    qDebug() << "readFile" << EasyLiving::readFile("D:/123-.txt");



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

    simpleLog = new SimpleLog("log.txt", true, this);
    simpleLog->append("afds");
    simpleLog->append("agg");
    EasyLiving::writeFile("1.txt", "aaaaaa");
    //simpleLog << "1";
    //sl << "asd";

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
    a->addGraphToPlot(ui->realTimeQcpPower);
    excelLog->addChannel(a);

    b = new ChannelDouble("BBB", EasyLiving::postfixMilli() + EasyLiving::postfixAmpere(), QStringList() << "b/middle2", this);
    connect(ui->dialB, &QDial::valueChanged, b, &ChannelDouble::setValue);
    excelLog->addChannel(b);

    c = new ChannelDouble("ЭЛВ/EnergyU get", this);
    //FIXME !tima45!
    //connect(ui->doubleSpinBoxC, &QDoubleSpinBox::valueChanged, c, &ChannelDouble::setValue);
    //connect(ui->doubleSpinBoxC, SIGNAL(valueChanged(double)), c, SLOT(setValue(double)));
    c->setValue(3.009);
    excelLog->addChannel(c);

    excelLog->finishConfigure();





}

void MainWindow::configureWorker()
{
    w = new Worker("test");
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

    timerrealTimeQcpReplot = new QTimer(this);
    timerrealTimeQcpReplot->setInterval(plotUpdateIntervalMSEC);
    connect(timerrealTimeQcpReplot, &QTimer::timeout, ui->realTimeQcpU, &RealTimeQCP::moveTimeAxisRealTime);
    timerrealTimeQcpReplot->start();
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

    graphRealTimeQcpUa->addData(now, 1000+1000*sin(5.0/2*cos(now)));
    graphRealTimeQcpIa->addData(now, 5+5*sin(9.0/2*cos(now)));
}

void MainWindow::addData2()
{
    auto now = RealTimeQCP::currentDateTime();

    graphRealTimeQcpUb->addData(now, 1000+1000*qPow(qSin(now), 2) - 2*qSin(now) - 2);
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
    auto message = QString("%1").arg(graphHighVoltageElvFull->valueCursor());
    this->setWindowTitle(message);
}


MainWindow::~MainWindow()
{
    timerAddData1->stop();
    delete timerAddData1;

    timerAddData2->stop();
    delete timerAddData2;

    delete excelLog;

    delete a;
    delete b;


    delete ui;
    delete mg;//->deleteLater();
}

void MainWindow::configureRealTimeQcpPlot()
{
    mg = new QCPMarginGroup(ui->realTimeQcpU->plot());

    RealTimeQCP * plot;

    plot = ui->realTimeQcpU;
    plot->configureAxis(plot->plot()->yAxis, tr("Напруга"), EasyLiving::postfixVolt(), 0, 2300);
    configureRealTimeQcpPlot(plot);
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQcpI->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQcpTemperature->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQcpPower->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQcpPersent->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQcpBool->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQcpVacuum->plot(), SLOT(replot()));
    connect(plot->plot(), SIGNAL(afterReplot()), ui->realTimeQcpRadiation->plot(), SLOT(replot()));

    plot = ui->realTimeQcpI;
    plot->configureAxis(plot->plot()->yAxis, tr("Тоооок"), EasyLiving::postfixMilliAmpere(), 0, 10, 2);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpTemperature;
    plot->configureAxis(plot->plot()->yAxis, tr("Температурим"), EasyLiving::postfixCelsius(), 0, 200);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpPower;
    plot->configureAxis(plot->plot()->yAxis, tr("МОООЩА!"), EasyLiving::postfixWatt(), 0, 700);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpPersent;
    plot->configureAxis(plot->plot()->yAxis, tr("Процентики"), EasyLiving::postfixPersent(), 0, 100);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpBool;
    plot->configureAxis(plot->plot()->yAxis, tr("True/False"), "", -0.2, 1.2);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTick(0, "False\nOff");
    textTicker->addTick(1, "True\nOn");
    plot->plot()->yAxis->setTicker(textTicker);
    //plot->plot()->yAxis->setSubTicks(false);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpVacuum;
    plot->configureAxis(plot->plot()->yAxis, tr("Вакуум"), "Pa", 1.0e-04, 1.0e+01, 0, QCPAxis::stLogarithmic);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpRadiation;
    plot->configureAxis(plot->plot()->yAxis, tr("Радиашн"), EasyLiving::postfixSievertPerHour(), 1.0e-07, 1.0e-01, 0, QCPAxis::stLogarithmic);
    configureRealTimeQcpPlot(plot);
}

void MainWindow::configureRealTimeQcpPlot(RealTimeQCP *plot)
{
    plot->setMarginGroup(mg);

    connect(plot, &RealTimeQCP::timeAxisRangeChanged, this, &MainWindow::realTimeQcpSetTimeAxisRange);
    connect(plot, &RealTimeQCP::cursorKeyChanged, this, &MainWindow::realTimeQcpSetCursorKey);
    connect(plot, &RealTimeQCP::realTimeChanged, this, &MainWindow::realTimeQcpSetRealTime);
    connect(plot, &RealTimeQCP::moveLineRealTimeChanged, this, &MainWindow::realTimeQcpSetMoveLineRealTime);

    connect(plot, &RealTimeQCP::cursor2VisibleValueChanged, this, &MainWindow::realTimeQcpSetCursor2Visible);
    connect(plot, &RealTimeQCP::cursor2KeyChanged, this, &MainWindow::realTimeQcpSetCursor2Key);
}

void MainWindow::configureRealTimeQcpGraphs()
{
    graphRealTimeQcpUa = ui->realTimeQcpU->addGraph("ELV/E", EasyLiving::postfixVolt(), 2);
    graphRealTimeQcpUb = ui->realTimeQcpU->addGraph("Ultravolt/-300", EasyLiving::postfixVolt());

    graphRealTimeQcpIa = ui->realTimeQcpI->addGraph("Bergoz/Hebl", EasyLiving::postfixMilliAmpere(), 3);

    graphRealTimeQcpBoola = ui->realTimeQcpBool->addGraph("ЭЛВ/Напуск аргона", "", 0);
}



/// { RealTimeQCP copy SIGNALS and SLOTS

void MainWindow::realTimeQcpSetTimeAxisRange(QCPRange range)
{

    auto _sender = dynamic_cast<RealTimeQCP *>(sender());

    ui->realTimeQcpU->setTimeAxisRange(range, _sender);
    ui->realTimeQcpI->setTimeAxisRange(range, _sender);
    ui->realTimeQcpTemperature->setTimeAxisRange(range, _sender);
    ui->realTimeQcpPower->setTimeAxisRange(range, _sender);
    ui->realTimeQcpPersent->setTimeAxisRange(range, _sender);
    ui->realTimeQcpBool->setTimeAxisRange(range, _sender);
    ui->realTimeQcpVacuum->setTimeAxisRange(range, _sender);
    ui->realTimeQcpRadiation->setTimeAxisRange(range, _sender);

}

void MainWindow::realTimeQcpSetCursorKey(double key)
{
    auto _sender = dynamic_cast<RealTimeQCP *>(sender());

    ui->realTimeQcpU->setCursorKey(key, _sender);
    ui->realTimeQcpI->setCursorKey(key, _sender);
    ui->realTimeQcpTemperature->setCursorKey(key, _sender);
    ui->realTimeQcpPower->setCursorKey(key, _sender);
    ui->realTimeQcpPersent->setCursorKey(key, _sender);
    ui->realTimeQcpBool->setCursorKey(key, _sender);
    ui->realTimeQcpVacuum->setCursorKey(key, _sender);
    ui->realTimeQcpRadiation->setCursorKey(key, _sender);

}

void MainWindow::realTimeQcpSetRealTime(bool newValue)
{
    auto _sender = dynamic_cast<RealTimeQCP *>(sender());

    ui->realTimeQcpU->setRealTime(newValue, _sender);
    ui->realTimeQcpI->setRealTime(newValue, _sender);
    ui->realTimeQcpTemperature->setRealTime(newValue, _sender);
    ui->realTimeQcpPower->setRealTime(newValue, _sender);
    ui->realTimeQcpPersent->setRealTime(newValue, _sender);
    ui->realTimeQcpBool->setRealTime(newValue, _sender);
    ui->realTimeQcpVacuum->setRealTime(newValue, _sender);
    ui->realTimeQcpRadiation->setRealTime(newValue, _sender);

}

void MainWindow::realTimeQcpSetMoveLineRealTime(bool newValue)
{
    auto _sender = dynamic_cast<RealTimeQCP *>(sender());

    ui->realTimeQcpU->setMoveLineRealTime(newValue, _sender);
    ui->realTimeQcpI->setMoveLineRealTime(newValue, _sender);
    ui->realTimeQcpTemperature->setMoveLineRealTime(newValue, _sender);
    ui->realTimeQcpPower->setMoveLineRealTime(newValue, _sender);
    ui->realTimeQcpPersent->setMoveLineRealTime(newValue, _sender);
    ui->realTimeQcpBool->setMoveLineRealTime(newValue, _sender);
    ui->realTimeQcpVacuum->setMoveLineRealTime(newValue, _sender);
    ui->realTimeQcpRadiation->setMoveLineRealTime(newValue, _sender);

}

void MainWindow::realTimeQcpSetCursor2Visible(bool newValue)
{
    auto _sender = dynamic_cast<RealTimeQCP *>(sender());

    ui->realTimeQcpU->setCursor2Visible(newValue, _sender);
    ui->realTimeQcpI->setCursor2Visible(newValue, _sender);
    ui->realTimeQcpTemperature->setCursor2Visible(newValue, _sender);
    ui->realTimeQcpPower->setCursor2Visible(newValue, _sender);
    ui->realTimeQcpPersent->setCursor2Visible(newValue, _sender);
    ui->realTimeQcpBool->setCursor2Visible(newValue, _sender);
    ui->realTimeQcpVacuum->setCursor2Visible(newValue, _sender);
    ui->realTimeQcpRadiation->setCursor2Visible(newValue, _sender);
}

void MainWindow::realTimeQcpSetCursor2Key(double key)
{
    auto _sender = dynamic_cast<RealTimeQCP *>(sender());

    ui->realTimeQcpU->setCursor2Key(key, _sender);
    ui->realTimeQcpI->setCursor2Key(key, _sender);
    ui->realTimeQcpTemperature->setCursor2Key(key, _sender);
    ui->realTimeQcpPower->setCursor2Key(key, _sender);
    ui->realTimeQcpPersent->setCursor2Key(key, _sender);
    ui->realTimeQcpBool->setCursor2Key(key, _sender);
    ui->realTimeQcpVacuum->setCursor2Key(key, _sender);
    ui->realTimeQcpRadiation->setCursor2Key(key, _sender);
}

/// } RealTimeQCP copy SIGNALS and SLOTS

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
