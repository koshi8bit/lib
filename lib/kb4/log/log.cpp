#include "log.h"

Log::Log(QObject *parent) : QObject(parent)
{
    timerCommit = new QTimer;
    timerCommit->setInterval(intervalCommitMSEC);
    connect(timerCommit, &QTimer::timeout, this, &Log::timeoutCommit, Qt::ConnectionType::QueuedConnection);

    timerPush = new QTimer;
    timerPush->setInterval(intervalPushSEC*1000);
    connect(timerPush, &QTimer::timeout, this, &Log::timeoutPush, Qt::ConnectionType::QueuedConnection);

    thread = new QThread;
    this->moveToThread(thread);
    thread->start();
}

void Log::addChannel(Channel *channel)
{
    channels.append(channel);
}


void Log::setAutoLog(bool newValue)
{
    if (!configureFinished && newValue)
    {
        finishConfigure();
        configureFinished = true;
    }

    if (newValue)
    {
        timerCommit->start();
        timerPush->start();
    }
    else
    {
        timerCommit->stop();
        timerPush->stop();
    }
}

QString Log::error()
{
    auto tmp = _error;
    _error.clear();
    return  tmp;
}

void Log::setError(QString message)
{
    _error.append(message);
}

void Log::timeoutCommit()
{
    commit();

    //FIXME more than 1000 mSec
//    auto dt = QDateTime::currentDateTime();
//    qDebug() << QString("COMM %1").arg(dt.toString("yyyy-MM-ddThh:mm:ss.zzz"));
}

void Log::timeoutPush()
{
    push();
}
