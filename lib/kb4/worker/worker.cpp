#include "worker.h"


Worker::Worker(QString name)
    :QObject()
{
    this->name = name;
    thread = new QThread();
    this->moveToThread(thread);
    thread->start();

    timer = new QTimer();
    connect(timer, &QTimer::timeout,
            this, &Worker::timerTimeout);
}

Worker::~Worker()
{
    timer->stop();
    thread->terminate(); //TODO quit

    timer->deleteLater();
    thread->deleteLater();
}

void Worker::start()
{
    timer->setInterval(0);
    timer->setSingleShot(true);
    timer->start();

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
    qCritical() << EL_FORMAT_ERR("Not implemented yet");

    timer->stop();
}

void Worker::timerTimeout()
{
    heavyWork();
    emit heavyWorkFinished();
    //timer->start();
}



