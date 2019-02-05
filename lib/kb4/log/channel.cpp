#include "channel.h"

Channel::Channel(QString plotText, QStringList logName, QObject *parent) : QObject(parent)
{
    this->_logName = logName;

    this->_plotText = QString("%1/%2")
            .arg(logName.join("/"))
            .arg(plotText);
    //this->_plotText = plotText;

    this->_uiText = plotText;
}

QString Channel::plotText()
{
    return _plotText;
}

QStringList Channel::logName()
{
    return _logName;
}


//QString Channel::toExcel(QStringList *list)
//{
//    return list->join(".");
//}

//QString Channel::toSQL(QStringList *list)
//{
//    return list->join("_");
//}
