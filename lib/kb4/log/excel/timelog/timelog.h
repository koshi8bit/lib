#ifndef TIMELOG_H
#define TIMELOG_H

#include <QDateTime>

#include <lib/kb4/log/excel/excel.h>
#include <lib/kb4/easyliving.h>


class TimeLog : public Excel
{
public:
    TimeLog();

protected:
    QString headersPrefix() override;
    QString commitPrefix() override;

};

#endif // TIMELOG_H
