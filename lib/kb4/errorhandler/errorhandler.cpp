#include "errorhandler.h"

ErrorHandler::ErrorHandler(QObject *parent) : QObject(parent)
{

}

void ErrorHandler::errorOccurred(QString message)
{
    auto date = QDateTime::currentDateTime().toString(datePattern);
}
