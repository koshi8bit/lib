#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include <lib/kb4/easyliving.h>


class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QString name);
    ~Worker();
    std::function<void()> heavyWork;

private:
    QThread *thread;
    QTimer *timer;
    QTimer *timerSingleTime;
    QString name;

signals:
    void heavyWorkSingleTimeFinished();
    void heavyWorkFinished();

public slots:
    void startSingleTime();
    void start(int intervalMSEC);

    void stop(bool waitOnePeriod = true);

private slots:
    void timerTimeout();
    void timerTimeoutSingleTime();

};

#endif // WORKER_H
