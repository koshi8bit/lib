#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QTimer>
#include <QThread>

#include <QDateTime>
#include <QDebug>


#include <lib/kb4/channel/channellog.h>

class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = nullptr);

    void addChannel(Channel *channel);
    void finishConfigure();

    virtual void push() = 0;
    virtual void commit() = 0;

private:
    int intervalCommitMSEC = 1000;
    int intervalPushSEC = 5;
    bool configureFinished = false;

    QTimer *timerCommit;
    QTimer *timerPush;
    QThread *thread;


protected:
    QList<ChannelLog *> channels;

    virtual void finishConfigureChild() = 0;

signals:
    void errorOcurred(QString message);

public slots:
    void setAutoLog(bool newValue);

protected slots:
    void timeoutCommit();
    void timeoutPush();
};

#endif // LOG_H
