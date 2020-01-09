#include "worker.h"


Worker::Worker(QString name)
    :QObject()
{
    this->name = name;
    thread = new QThread();
    this->moveToThread(thread);

}

void Worker::start()
{
    heavyWork();
    emit heavyWorkFinished();
}

void Worker::start(int intervalMSEC)
{
    timer = new QTimer;
    timer->setInterval(intervalMSEC);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &Worker::timerTimeout);
    timer->start();
}

void Worker::timerTimeout()
{
    heavyWork();
    emit heavyWorkFinished();
    timer->start();
}



