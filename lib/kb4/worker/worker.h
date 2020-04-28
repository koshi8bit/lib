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
    QString name;

signals:
    void heavyWorkFinished();

public slots:
    void start();
    void start(int intervalMSEC);

    void stop(bool waitOnePeriod = true);

private slots:
    void timerTimeout();


};

#endif // WORKER_H
