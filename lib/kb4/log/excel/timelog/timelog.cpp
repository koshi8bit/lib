#include "timelog.h"

TimeLog::TimeLog(HeaderMode headerMode, QString externalFolder, QObject *parent)
    : Excel(headerMode, externalFolder, parent)

{

}

QString TimeLog::headersPrefix(TimePrefixLanguage timePrefixLanguage)
{
    QString date;
    QString dateFull;
    if (timePrefixLanguage == TimePrefixLanguage::En)
    {
        date = "Date";
        dateFull = "Date full";
    }

    if (timePrefixLanguage == TimePrefixLanguage::Ru)
    {
        date = "Дата";
        dateFull = "Полная дата";
    }

    return QString("%1%2%3%4")
            .arg(date)
            .arg(elementDelimeter)
            .arg(dateFull)
            .arg(elementDelimeter);
}

QString TimeLog::commitPrefix()
{
    auto dt = QDateTime::currentDateTime();
    return QString("%1%2%3%4")
            .arg(dt.toString("hh:mm:ss"))
            .arg(elementDelimeter)
            .arg(dt.toString("yyyy-MM-ddThh:mm:ss.zzz"))
            .arg(elementDelimeter);
}
