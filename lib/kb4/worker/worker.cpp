#include "worker.h"


Worker::Worker(QString name)
    :QObject()
{
    this->name = name;
    thread = new QThread();
    this->moveToThread(thread);
    thread->start();

    timer = new QTimer();
    timer->setSingleShot(false);
    connect(timer, &QTimer::timeout,
            this, &Worker::timerTimeout);

    timerSingleTime = new QTimer();
    timerSingleTime->setInterval(0);
    timerSingleTime->setSingleShot(true);
    connect(timerSingleTime, &QTimer::timeout,
            this, &Worker::timerTimeoutSingleTime);

}

Worker::~Worker()
{
    timer->stop();
    thread->terminate(); //TODO quit

    timer->deleteLater();
    timerSingleTime->deleteLater();
    thread->deleteLater();
}

void Worker::startSingleTime()
{
    timerSingleTime->start();

//    heavyWork();
//    emit heavyWorkFinished();
}

void Worker::start(int intervalMSEC)
{
    timer->setInterval(intervalMSEC);
    //FIXME если процесс занимает больше времени, чем интервал - то на стеке он будет копиться.
    //мб вообще нах таймер?
    //timer->setSingleShot(true);

    timer->start();
}

void Worker::stop(bool waitOnePeriod)
{
    Q_UNUSED(waitOnePeriod)
    //qCritical() << EL_FORMAT_ERR("Not implemented yet");

    timer->stop();
    timerSingleTime->stop();
}

void Worker::timerTimeout()
{
    heavyWork();
    emit heavyWorkFinished();

    //timer->start();
}

void Worker::timerTimeoutSingleTime()
{
    heavyWork();
    emit heavyWorkSingleTimeFinished();
}



