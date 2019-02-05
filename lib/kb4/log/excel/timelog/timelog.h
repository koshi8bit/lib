#ifndef TIMELOG_H
#define TIMELOG_H

#include <QDateTime>

#include <lib/kb4/log/excel/excel.h>


class TimeLog : public Excel
{
public:
    TimeLog(QString path, HeaderMode headerMode, QObject *parent = nullptr);

protected:
    QString headersPrefix(TimePrefixLanguage timePrefixLanguage) override;
    QString commitPrefix() override;

};

#endif // TIMELOG_H
