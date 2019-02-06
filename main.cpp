#include "mainwindow.h"
#include <QApplication>


#include <QApplication>
#include <QDebug>
#include <QDateTime>
#include <QString>
#include <lib/kb4/macro.h>

static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(0);

QString filename;

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
    auto time =  QDateTime::currentDateTime().toString(KB4_FORMAT_DATETIME_UI);
    writeMessage(QString("%1: %2\n").arg(time, msg));

    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}

void configureQDebug()
{
    //filename = "qDebug.log";
    filename = QString("qDebug-%1.log").arg(QDateTime::currentDateTime().toString(KB4_FORMAT_DATETIME_FILE));
    qInstallMessageHandler(myCustomMessageHandler);
    writeMessage("\n");
    qDebug() << "App started";
}

int main(int argc, char *argv[])
{
    //configureQDebug();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
