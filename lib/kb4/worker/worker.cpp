#include "worker.h"


Worker::Worker(QString name, QObject *parent)
    :QObject(parent)
{
    this->name = name;
    thread = new QThread(parent);
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
}

void Worker::timerTimeout()
{
    heavyWork();
    emit heavyWorkFinished();
    timer->start();
}



