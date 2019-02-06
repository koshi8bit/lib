#ifndef QDEBUGLOGGER_H
#define QDEBUGLOGGER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QString>

#include <lib/kb4/macro.h>

class QDebugLogger : public QObject
{
    Q_OBJECT
public:
    explicit QDebugLogger(QObject *parent = nullptr);
    static void configure();

private:
    static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER;
    static const QString filename;

    static void writeMessage(QString msg);
    static void myCustomMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);


signals:

public slots:
};

#endif // QDEBUGLOGGER_H
