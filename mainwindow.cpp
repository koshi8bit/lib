#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(EasyLiving::setWindowTitle("Tests"));

    settings = new QSettings("settings.ini", QSettings::IniFormat, this);
    if(settings->value("qDebug/saveToFile", false).toBool())
        configureQDebug();

    configureRealTimeQcpPlot();
    configureRealTimeQcpGraphs();
    configureTimers();

    configureRealTimeQcpPlotDayStyle();

    configureGradientLineEdit();

    configureExcelLog();

    configureWorker();

    configureValueDouble();
    doubleValueScaleTest();

    writeFileTest();

    eh.checkForErrors();

    qLocaleTest();

    simpleLogTest();

    dateTimeDeltaTests();
    pathConcatTest();
    radarPlotTest();

    testingGraphErrorXY();

    testingValueBuffered();

    configureFaults();
}


void MainWindow::testingValueBuffered()
{
    auto a = new ChannelDouble("1");
    a->setBufferSize(10);

    a->setValue(1.1);
    qDebug() << a->valueBuffered(); // 1.1
    a->setValue(2);
    qDebug() << a->valueBuffered(); // 1.55
    a->setValue(3);
    a->setValue(3);
    a->setValue(3);
    a->setValue(6.2);
    a->setValue(3);
    a->setValue(1);
    a->setValue(3);
    a->setValue(3);
    qDebug() << a->valueBuffered(); // 2.83
    a->setValue(2.2);
    qDebug() << a->valueBuffered(); // 2.94
}

void MainWindow::testingGraphErrorXY()
{
    auto sg = ui->simplePLot->addGraphErrorXY("tst");
    qDebug() << "started test";
    sg->addData(2, 2, 0.2, 0.2, 0.2, 0.2);
    sg->addData(1, 1, 0.1, 0.1, 0.1, 0.1);
    sg->addData(3, 3, 0.3, 0.3, 0.3, 0.3);
    //sg->addData(0, 0, 0.5, 0.5, 0.6, 0.6);
}


void MainWindow::doubleValueScaleTest()
{
    auto a = new ChannelDouble("a");
    a->setScaling(0, 24, 0, 10);
    a->setRawValue(2);
    qDebug() << "value" <<a->value();
    a->setValue(8);
    qDebug() << "rawValue" <<a->rawValue();
}

void MainWindow::configureValueDouble()
{
    ui->valuedoubleTest->configure("Ток", EasyLiving::postfixMilliAmpere());
    connect(ui->valuedoubleTest, &ValueDouble::valueCopyedToClipboard, this, &MainWindow::valueDoubleCopyedToClipboard);
    ui->valuedoubleTest->setValue(8.7);

    ui->valuedoubleTest_2->configure("Ток", EasyLiving::postfixMilliAmpere(), 2, false, true);
    connect(ui->valuedoubleTest_2, &ValueDouble::valueCopyedToClipboard, this, &MainWindow::valueDoubleCopyedToClipboard);
    ui->valuedoubleTest_2->setValue(8.7654);

    connect(ui->valuedoubleTest_2, &ValueDouble::valueChanged, ui->valuedoubleTest_2, &ValueDouble::setValue);
    connect(ui->valuedoubleTest_2, &ValueDouble::valueChanged, [](double a) { qDebug() << a; });
}

void MainWindow::qLocaleTest()
{
    auto a = QLocale(QLocale::Russian);
    qDebug() << "Разделитель тчк/зпт" << a.decimalPoint();
    qDebug() << "Разделитель группы" << QString(a.groupSeparator());
    //qDebug() << QString::number(1300.2, 'f', 2);
    a.setNumberOptions(QLocale::OmitGroupSeparator);
    qDebug() << a.toString(1300.2, 'f', 2);
}

void MainWindow::writeFileTest()
{
    //    qDebug() << "writeFile" << EasyLiving::writeFile("D:/123-.txt", "sup bro\nsup buddy", false);
    //    qDebug() << "readFile" << EasyLiving::readFile("D:/123-.txt");

    EasyLiving::writeFile("1.txt", "aaaaaa");
    //simpleLog << "1";
    //sl << "asd";
}

void MainWindow::simpleLogTest()
{
    simpleLog = new SimpleLog("log.txt", true, this);
    simpleLog->append("afds");
    simpleLog->append("agg");
}

void MainWindow::radarPlotTest()
{
    auto up = new ChannelDouble("Up", EasyLiving::postfixCelsius(), this);
    connect(ui->dialUp, &QDial::valueChanged, up, &ChannelDouble::setValue);

    auto right = new ChannelDouble("Right", EasyLiving::postfixCelsius(), this);
    connect(ui->dialRight, &QDial::valueChanged, right, &ChannelDouble::setValue);

    auto down = new ChannelDouble("Down", EasyLiving::postfixCelsius(), this);
    connect(ui->dialDown, &QDial::valueChanged, down, &ChannelDouble::setValue);

    auto left = new ChannelDouble("Left", EasyLiving::postfixCelsius(), this);
    connect(ui->dialLeft, &QDial::valueChanged, left, &ChannelDouble::setValue);


    radarTestGraph = ui->radarTemperature4Plot->addGraph("1 ДК", up, right, down, left);
    //radarTestGraph->setOffset(15);
    radarTestGraph->setColor(QColor("#CC0000"));

    ui->radarPlot->setVisible(false);

//    radarTestGraph = ui->radarTemperature4Plot->addGraph("2 ДК", 1, false, 5);
//    radarTestGraph->setColor(QColor("#00CC00"));

//    radarTestGraph = ui->radarTemperature4Plot->addGraph("3 ДК", 1, false, 5);
//    radarTestGraph->setColor(QColor("#0000CC"));

//    radarTestGraph = ui->radarTemperature4Plot->addGraph("4 ДК", 1, false, 5);
//    radarTestGraph->setColor(QColor("#AA99AA"));
}

void MainWindow::pathConcatTest()
{
    qDebug() << EasyLiving::pathConcat("C:/1", "2\\3");
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
    b->setRange(1, 33.3);
    connect(b, &ChannelDouble::inRangeChanged, [this](bool inRange) {
       qDebug() << inRange;
    });

    c = new ChannelDouble("ЭЛВ/EnergyU get", this);
    //FIXME !tima45!
    //connect(ui->doubleSpinBoxC, &QDoubleSpinBox::valueChanged, c, &ChannelDouble::setValue);
    //connect(ui->doubleSpinBoxC, SIGNAL(valueChanged(double)), c, SLOT(setValue(double)));
    c->setValue(3.009);
    excelLog->addChannel(c);



    d = new ChannelDouble("DDD", EasyLiving::postfixSievertPerHour(), this);
    connect(ui->valuedoubleD, &ValueDouble::valueChanged, d, &ChannelDouble::valueChanged);
    d->setScientificNotation(true);
    excelLog->addChannel(d);

    ui->valuedoubleD->configure(d, d);
    //ui->valuedoubleD->setValue(8.7654);
    //connect(ui->valuedoubleD, &ValueDouble::valueChanged, ui->valuedoubleD, &ValueDouble::setValue);

    t = new ChannelT<QDateTime>("time", "", this);
    excelLog->addChannel(t);

    excelLog->finishConfigure();
}

void MainWindow::configureWorker()
{
    w = new Worker("test");
    w->heavyWork = [this]() { this->heavyWork(); };

    //w->start(1000);
}

void MainWindow::heavyWork()
{
    qDebug() << QDateTime::currentDateTime().toString(EasyLiving::formatTimeUi(true)) << "heavyWork started";
    QThread::msleep(2000);
    qDebug() << QDateTime::currentDateTime().toString(EasyLiving::formatTimeUi(true)) << "heavyWork stopped";
}

void MainWindow::valueDoubleCopyedToClipboard(QString newValue, QString message)
{
    Q_UNUSED(newValue)
    ui->statusBar->showMessage(message, 5000);
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

    timerRealTimeQcpReplot = new QTimer(this);
    timerRealTimeQcpReplot->setInterval(plotUpdateIntervalMSEC);
    connect(timerRealTimeQcpReplot, &QTimer::timeout, ui->realTimeQcpU, &RealTimePlot::moveTimeAxisRealTime);
    timerRealTimeQcpReplot->start();
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
    auto now = RealTimePlot::currentDateTime();

    graphRealTimeQcpUa->addData(now, 1000+1000*sin(5.0/2*cos(now)));
    graphRealTimeQcpIa->addData(now, 5+5*sin(9.0/2*cos(now)));
}

void MainWindow::addData2()
{
    auto now = RealTimePlot::currentDateTime();

    graphRealTimeQcpUb->addData(now, 5+5*qPow(qSin(now), 2) - 2*qSin(now) - 2);
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
    delete mgColumn0;//->deleteLater();
    delete mgColumn1;//->deleteLater();
}

void MainWindow::dateTimeDeltaTests()
{
    //    QTime t1(15, 23, 16);
    //    QTime t2(12, 11, 02);

    //    qDebug() << t2.secsTo(t1);
    //    QTime t3 = QTime(0, 0, 0).addSecs(t2.secsTo(t1));

    //    qDebug() << t3;

    QDateTime begin(QDate(2020, 3, 1), QTime(9, 0, 0));
    QDateTime end(QDate(2021, 3, 1), QTime(9, 0, 0));

    qDebug() << EasyLiving::dateTimeDelta(begin, end);

//    QDateTime interval = QDateTime::fromMSecsSinceEpoch(begin.toMSecsSinceEpoch() - end.toMSecsSinceEpoch());
//    interval = interval.addYears(-1970);
//    qDebug() << interval.toString(EasyLiving::formatDateTimeUi());
//    int years;
//    int month;
//    int days;
//    int hours;
//    int minutes;
//    int seconds;
//    int milliseconds;
//    EasyLiving::dateTimeDelta(begin, end, years, month, days, hours, minutes, seconds, milliseconds);
    //    qDebug() << years << month << days << hours;// << minutes << seconds << milliseconds;
}

void MainWindow::configureFaults()
{
    faultsWidget = new FaultsWidget(ui->scrollAreaFaults);
    faultsWidget->configureBorder(ui->labelFaultBorderTL,
                                 ui->labelFaultBorderT,
                                 ui->labelFaultBorderTR,
                                 ui->labelFaultBorderL,
                                 ui->labelFaultBorderR,
                                 ui->labelFaultBorderBL,
                                 ui->labelFaultBorderB,
                                 ui->labelFaultBorderBR);
    faultsWidget->configureSharedVariable(false);

    connect(faultsWidget, &FaultsWidget::faultTriggered,
            ui->checkBoxFaults, &QCheckBox::setChecked);

    fault1 = new Fault("fault1", this);
    faultsWidget->addFault(fault1);

    fault2 = new Fault("fault2", this);
    faultsWidget->addFault(fault2);


}

void MainWindow::configureRealTimeQcpPlot()
{
    mgColumn0 = new QCPMarginGroup(ui->realTimeQcpU->qcp());
    mgColumn1 = new QCPMarginGroup(ui->realTimeQcpI->qcp());


    RealTimePlot * plot;

    plot = ui->realTimeQcpU;
    plot->configureAxis(plot->qcp()->yAxis, tr("Напруга"), EasyLiving::postfixKiloVolt(), 0, 2300);
    plot->configureAxis(plot->qcp()->yAxis2, tr("Напруга"), EasyLiving::postfixVolt(), 0, 10);
    plot->setMarginGroup(mgColumn0);

    configureRealTimeQcpPlot(plot);
    connect(plot->qcp(), SIGNAL(afterReplot()), ui->realTimeQcpI->qcp(), SLOT(replot()));
    connect(plot->qcp(), SIGNAL(afterReplot()), ui->realTimeQcpTemperature->qcp(), SLOT(replot()));
    connect(plot->qcp(), SIGNAL(afterReplot()), ui->realTimeQcpPower->qcp(), SLOT(replot()));
    connect(plot->qcp(), SIGNAL(afterReplot()), ui->realTimeQcpPersent->qcp(), SLOT(replot()));
    connect(plot->qcp(), SIGNAL(afterReplot()), ui->realTimeQcpBool->qcp(), SLOT(replot()));
    connect(plot->qcp(), SIGNAL(afterReplot()), ui->realTimeQcpVacuum->qcp(), SLOT(replot()));
    connect(plot->qcp(), SIGNAL(afterReplot()), ui->realTimeQcpRadiation->qcp(), SLOT(replot()));

    plot = ui->realTimeQcpI;
    plot->configureAxis(plot->qcp()->yAxis, tr("Тоооок"), EasyLiving::postfixMilliAmpere(), 0, 10, 2);
    plot->setMarginGroup(mgColumn1);

    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpTemperature;
    plot->configureAxis(plot->qcp()->yAxis, tr("Температурим"), EasyLiving::postfixCelsius(), 0, 200);
    plot->setMarginGroup(mgColumn0);

    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpPower;
    plot->configureAxis(plot->qcp()->yAxis, tr("МОООЩА!"), EasyLiving::postfixWatt(), 0, 700);
    plot->setMarginGroup(mgColumn1);

    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpPersent;
    plot->configureAxis(plot->qcp()->yAxis, tr("Процентики"), EasyLiving::postfixPersent(), 0, 100);
    plot->setMarginGroup(mgColumn0);

    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpBool;
    plot->configureAxis(plot->qcp()->yAxis, tr("True/False"), "", -0.2, 1.2);
    plot->setMarginGroup(mgColumn1);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTick(0, "False\nOff");
    textTicker->addTick(1, "True\nOn");
    plot->qcp()->yAxis->setTicker(textTicker);
    //plot->plot()->yAxis->setSubTicks(false);
    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpVacuum;
    plot->configureAxis(plot->qcp()->yAxis, tr("Вакуум"), "Pa", 1.0e-04, 1.0e+01, 0, QCPAxis::stLogarithmic);
    plot->setMarginGroup(mgColumn0);

    configureRealTimeQcpPlot(plot);

    plot = ui->realTimeQcpRadiation;
    plot->configureAxis(plot->qcp()->yAxis, tr("Радиашн"), EasyLiving::postfixSievertPerHour(), 1.0e-07, 1.0e-01, 0, QCPAxis::stLogarithmic);
    plot->setMarginGroup(mgColumn1);

    configureRealTimeQcpPlot(plot);
}

void MainWindow::configureRealTimeQcpPlot(RealTimePlot *plot)
{
    connect(plot, &RealTimePlot::timeAxisRangeChanged, this, &MainWindow::realTimeQcpSetTimeAxisRange);
    connect(plot, &RealTimePlot::cursorKeyChanged, this, &MainWindow::realTimeQcpSetCursorKey);
    connect(plot, &RealTimePlot::realTimeChanged, this, &MainWindow::realTimeQcpSetRealTime);
    connect(plot, &RealTimePlot::moveLineRealTimeChanged, this, &MainWindow::realTimeQcpSetMoveLineRealTime);

    connect(plot, &RealTimePlot::cursor2VisibleValueChanged, this, &MainWindow::realTimeQcpSetCursor2Visible);
    connect(plot, &RealTimePlot::cursor2KeyChanged, this, &MainWindow::realTimeQcpSetCursor2Key);
}

void MainWindow::configureRealTimeQcpGraphs()
{
    graphRealTimeQcpUa = ui->realTimeQcpU->addGraph(ui->realTimeQcpU->qcp()->yAxis, "ELV/E", EasyLiving::postfixVolt(), 1);
    graphRealTimeQcpUb = ui->realTimeQcpU->addGraph(ui->realTimeQcpU->qcp()->yAxis2, "Ultravolt/-300", EasyLiving::postfixVolt());

    graphRealTimeQcpIa = ui->realTimeQcpI->addGraph("Bergoz/Hebl", EasyLiving::postfixMilliAmpere(), 3);

    graphRealTimeQcpBoola = ui->realTimeQcpBool->addGraph("ЭЛВ/Напуск аргона", "", 0);
}

void MainWindow::configureRealTimeQcpPlotDayStyle()
{
    auto plot = ui->realTimeQcpDayStyle;
    plot->configureAxis(plot->qcp()->yAxis, tr("Шкала"), "", 0, 10, 2);
    plot->setDayStyle(true, false);
}



/// { RealTimeQCP copy SIGNALS and SLOTS

void MainWindow::realTimeQcpSetTimeAxisRange(QCPRange range)
{

    auto _sender = dynamic_cast<RealTimePlot *>(sender());

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
    auto _sender = dynamic_cast<RealTimePlot *>(sender());

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
    auto _sender = dynamic_cast<RealTimePlot *>(sender());

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
    auto _sender = dynamic_cast<RealTimePlot *>(sender());

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
    auto _sender = dynamic_cast<RealTimePlot *>(sender());

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
    auto _sender = dynamic_cast<RealTimePlot *>(sender());

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

void MainWindow::on_pushButtonNow_clicked()
{
    t->setValue(QDateTime::currentDateTime());
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << size();
    this->resize(QSize(1324, 790));
    ui->realTimeQcpU->setTimeAxisRange(35);
}

static const int textMargins = 12; // in millimeters
//static const int borderMargins = 10; // in millimeters

static double mmToPixels(QPrinter& printer, int mm)
{
    return mm * 0.039370147 * printer.resolution();
}

static void paintPage(int pageNumber, int pageCount,
                      QPainter* painter, QTextDocument* doc,
                      const QRectF& textRect, qreal footerHeight)
{
    Q_UNUSED(pageCount)

    painter->save();
    // textPageRect is the rectangle in the coordinate system of the QTextDocument, in pixels,
    // and starting at (0,0) for the first page. Second page is at y=doc->pageSize().height().
    const QRectF textPageRect(0, pageNumber * doc->pageSize().height(), doc->pageSize().width(), doc->pageSize().height());
    // Clip the drawing so that the text of the other pages doesn't appear in the margins
    painter->setClipRect(textRect);
    // Translate so that 0,0 is now the page corner
    painter->translate(0, -textPageRect.top());
    // Translate so that 0,0 is the text rect corner
    painter->translate(textRect.left(), textRect.top());
    doc->drawContents(painter);
    painter->restore();
    QRectF footerRect = textRect;
    footerRect.setTop(textRect.bottom());
    footerRect.setHeight(footerHeight);
    //painter->drawText(footerRect, Qt::AlignVCenter | Qt::AlignRight, QObject::tr("Page %1 of %2").arg(pageNumber+1).arg(pageCount));
}

static void printDocument(QPrinter& printer, QTextDocument* doc)
{
    QPainter painter( &printer );
    doc->documentLayout()->setPaintDevice(&printer);
    doc->setPageSize(printer.pageRect().size());
    QSizeF pageSize = printer.pageRect().size(); // page size in pixels
    // Calculate the rectangle where to lay out the text
    const double tm = mmToPixels(printer, textMargins);
    const qreal footerHeight = painter.fontMetrics().height();
    const QRectF textRect(tm, tm, pageSize.width() - 2 * tm, pageSize.height() - 2 * tm - footerHeight);
    doc->setPageSize(textRect.size());

    const int pageCount = doc->pageCount();

    bool firstPage = true;
    for (int pageIndex = 0; pageIndex < pageCount; ++pageIndex) {

        if (!firstPage)
            printer.newPage();

        paintPage(pageIndex, pageCount, &painter, doc, textRect, footerHeight );
        firstPage = false;
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QTextDocument *document = new QTextDocument();
    QTextCursor cursor(document);
    QTextBlockFormat blockFormat;


    for(int i=0; i < 10; i++)
    {
       cursor.insertBlock(blockFormat);
       cursor.insertHtml(QString("<h1>This is the %1 page</h1>").arg(i+1));
       blockFormat.setPageBreakPolicy(QTextFormat::PageBreak_AlwaysBefore);
    }


    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("filename.pdf");

    printDocument(printer, document);
}

void MainWindow::on_doubleSpinBoxRadarRadius_valueChanged(double arg1)
{
    radarTestGraph->setRadius(arg1);
    ui->radarTemperature4Plot->qcp()->replot();
}

void MainWindow::on_doubleSpinBoxRadarAngle_valueChanged(double arg1)
{
    radarTestGraph->setAngle(arg1);
    ui->radarTemperature4Plot->qcp()->replot();
}

void MainWindow::on_pushButtonRadarCalc_clicked()
{
    radarTestGraph->calcDeviation();
    ui->radarTemperature4Plot->replot();
}


void MainWindow::on_pushButtonAddPlot_clicked()
{
    qDebug() << "under constraction..";
    deletingTest = new ChannelDouble("deletingTest");
    deletingTest->addGraphToPlot(ui->realTimeQcpVacuum);

    ui->pushButtonDeletePlot->setEnabled(true);
}

void MainWindow::on_pushButtonDeletePlot_clicked()
{
    qDebug() << "under constraction..";
    delete deletingTest;
    ui->pushButtonDeletePlot->setEnabled(false);
}

void MainWindow::on_pushButton_7_clicked()
{
    w->startSingleTime();
}

void MainWindow::on_pushButton_8_clicked()
{
    qDebug() << timer->isActive();
    timer->start();
}

void MainWindow::on_checkBoxFault1_toggled(bool checked)
{
    fault1->setVisible(checked);
}

void MainWindow::on_checkBoxFault2_toggled(bool checked)
{
    fault2->setVisible(checked);
}
