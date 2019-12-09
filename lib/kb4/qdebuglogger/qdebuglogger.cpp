#include "qdebuglogger.h"

static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(0);

QString filename = "./qDebug.txt";

void writeMessage(QString msg)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        QTextStream stream(&file);
        stream << msg;
    }
}

void myCustomMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    auto time =  QDateTime::currentDateTime().toString(EasyLiving::formatDateTimeUi(true));
    writeMessage(QString("%1: %2\n").arg(time, msg));

    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}

void configureQDebug()
{
    qInstallMessageHandler(myCustomMessageHandler);
    writeMessage("\n");
    qDebug() << "qDebug file dump started";
}
