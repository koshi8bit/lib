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

    configureRealTimeQcpPlotDayStyle();

    configureTimers();

    configureGradientLineEdit();

    configureExcelLog();

    configureWorker();

    ui->valuedoubleTest->configure("Ток", EasyLiving::postfixMilliAmpere());
    connect(ui->valuedoubleTest, &ValueDouble::valueCopyedToClipboard, this, &MainWindow::valueDoubleCopyedToClipboard);
    ui->valuedoubleTest->setValue(8.7);

    ui->valuedoubleTest_2->configure("Ток", EasyLiving::postfixMilliAmpere(), 2, false, true);
    connect(ui->valuedoubleTest_2, &ValueDouble::valueCopyedToClipboard, this, &MainWindow::valueDoubleCopyedToClipboard);
    ui->valuedoubleTest_2->setValue(8.7654);


    connect(ui->valuedoubleTest_2, &ValueDouble::valueChanged, ui->valuedoubleTest_2, &ValueDouble::setValue);
    connect(ui->valuedoubleTest_2, &ValueDouble::valueChanged, [](double a) { qDebug() << a; });

//    qDebug() << "writeFile" << EasyLiving::writeFile("D:/123-.txt", "sup bro\nsup buddy", false);
//    qDebug() << "readFile" << EasyLiving::readFile("D:/123-.txt");



    eh.checkForErrors();

    auto a = QLocale(QLocale::Russian);
    qDebug() << "Разделитель тчк/зпт" << a.decimalPoint();
    qDebug() << "Разделитель группы" << QString(a.groupSeparator());
    //qDebug() << QString::number(1300.2, 'f', 2);
    a.setNumberOptions(QLocale::OmitGroupSeparator);
    qDebug() << a.toString(1300.2, 'f', 2);


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

    qDebug() << EasyLiving::pathConcat("C:/1", "2\\3");

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

    //auto temperatureD1 = new RadarGraph("name", "postfix", this);
    //temperatureD1->addGraphToPlot(ui->radarQcp);

    radarTestGraph = ui->radarQcp->addGraph("1 ДК", EasyLiving::postfixCelsius(), 1, false, 5);
    radarTestGraph->setColor(QColor("#CC0000"));

    radarTestGraph = ui->radarQcp->addGraph("2 ДК", EasyLiving::postfixCelsius(), 1, false, 5);
    radarTestGraph->setColor(QColor("#00CC00"));

    radarTestGraph = ui->radarQcp->addGraph("3 ДК", EasyLiving::postfixCelsius(), 1, false, 5);
    radarTestGraph->setColor(QColor("#0000CC"));

    radarTestGraph = ui->radarQcp->addGraph("4 ДК", EasyLiving::postfixCelsius(), 1, false, 5);
    radarTestGraph->setColor(QColor("#AA99AA"));


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

    t = new ChannelT<QDateTime>("time", "", this);
    excelLog->addChannel(t);

    excelLog->finishConfigure();





}

void MainWindow::configureWorker()
{
    w = new Worker("test");
    w->heavyWork = [this]() { this->heavyWork();};
    w->start(1000);
}

void MainWindow::heavyWork()
{
    qDebug() << "heavyWork";
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

void MainWindow::configureRealTimeQcpPlotDayStyle()
{
    auto plot = ui->realTimeQcpDayStyle;
    plot->configureAxis(plot->plot()->yAxis, tr("Шкала"), "", 0, 10, 2);
    plot->setDayStyle(true, false);
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
static const int borderMargins = 10; // in millimeters

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


    for(int i=0; i < 10; i++){
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
    ui->radarQcp->qcp()->replot();
}

void MainWindow::on_doubleSpinBoxRadarAngle_valueChanged(double arg1)
{
    radarTestGraph->setAngle(arg1);
    ui->radarQcp->qcp()->replot();
}
