#include "qdebuglogger.h"

const QtMessageHandler QDebugLogger::QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);
const QString filename = QString("qDebug-%1.log").arg(QDateTime::currentDateTime().toString(KB4_FORMAT_DATETIME_FILE));;

QDebugLogger::QDebugLogger(QObject *parent) : QObject(parent)
{

}



void QDebugLogger::writeMessage(QString msg)
{
    QFile file(QDebugLogger::filename);
    if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        QTextStream stream(&file);
        stream << msg;
    }
}

void QDebugLogger::myCustomMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    auto time =  QDateTime::currentDateTime().toString(KB4_FORMAT_DATETIME_UI);
    writeMessage(QString("%1: %2\n").arg(time, msg));

    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}

void QDebugLogger::configure()
{
    //filename = "qDebug.log";
    qInstallMessageHandler(myCustomMessageHandler);
    writeMessage("\n");
    qDebug() << "App started";
}
