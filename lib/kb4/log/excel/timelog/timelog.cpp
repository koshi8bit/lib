#include "timelog.h"

TimeLog::TimeLog(QString path, HeaderMode headerMode, QObject *parent)
    : Excel(path, headerMode, parent)

{

}

QString TimeLog::headersPrefix(TimePrefixLanguage timePrefixLanguage)
{
    QString date;
    QString dateFull;
    if (timePrefixLanguage == TimePrefixLanguage::En)
    {
        date = "Time";
        dateFull = "Full date";
    }

    if (timePrefixLanguage == TimePrefixLanguage::Ru)
    {
        date = "Время";
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
            .arg(dt.toString(KB4_FORMAT_TIME_UI_NO_MS))
            .arg(elementDelimeter)
            .arg(dt.toString(KB4_FORMAT_DATETIME_UI))
            .arg(elementDelimeter);
}
