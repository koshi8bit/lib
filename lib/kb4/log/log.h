#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QTimer>
#include <QThread>

#include <QDateTime>
#include <QDebug>


#include "channel.h"

class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = nullptr);

    void addChannel(Channel *channel);
    void finishConfigure();

    virtual void push() = 0;
    virtual void commit() = 0;

    QString error();


private:
    int intervalCommitMSEC = 1000;
    int intervalPushSEC = 5;
    bool configureFinished = false;

    QTimer *timerCommit;
    QTimer *timerPush;
    QThread *thread;

    QString _error;


protected:
    QList<Channel *> channels;

    virtual void finishConfigureChild() = 0;

    void setError(QString message);

signals:
    void errorOcurred(QString message);

public slots:
    void setAutoLog(bool newValue);

protected slots:
    void timeoutCommit();
    void timeoutPush();
};

#endif // LOG_H
