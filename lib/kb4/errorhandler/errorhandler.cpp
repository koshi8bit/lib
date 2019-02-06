#include "errorhandler.h"

ErrorHandler::ErrorHandler(QObject *parent) : QObject(parent)
{

}

void ErrorHandler::errorOccurred(QString message)
{
    auto date = QDateTime::currentDateTime().toString(KB4_FORMAT_DATETIME_FILE);
    auto fileName = QString("crash-%1.log").arg(date);
    auto file = new QFile(fileName);

    if (!file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << message;
        QMessageBox mb;
        mb.setIcon(QMessageBox::Critical);
    }
}

bool ErrorHandler::openFile()
{
    if ())
    {
        stream = new QTextStream(file);
        return true;
    }
    return false;
}
