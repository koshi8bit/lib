#ifndef TIMELOG_H
#define TIMELOG_H

#include <QDateTime>

#include <lib/kb4/log/excel/excel.h>


class TimeLog : public Excel
{
public:
    TimeLog(QObject *parent = nullptr);

protected:
    QString headersPrefix() override;
    QString commitPrefix() override;

};

#endif // TIMELOG_H
