#ifndef EXCEL_H
#define EXCEL_H

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QDir>

#include <lib/kb4/log/log.h>
#include <lib/kb4/log/channelt.h>
#include <lib/kb4/macro.h>

#include "excelfile.h"


class Excel : public Log
{

public:
    enum HeaderModeFlag {
        NoHeader = 0x0000,
        PlotText = 0x0001,
        LogName = 0x0002,
        UiText = 0x0004
    };
    Q_DECLARE_FLAGS(HeaderMode, HeaderModeFlag)

    enum TimePrefixLanguage {
        Ru,
        En
    };
    Q_ENUM(TimePrefixLanguage)

    Excel(QObject *parent = nullptr);
    ~Excel();

    void configure(QString path, HeaderMode headerMode);

    void push() override;
    void commit() override;

protected:
    static const QString elementDelimeter;
    static const QString lineDelimeter;
    static QString formatDoubleValue(double value);

    HeaderMode headerMode;
    void finishConfigureChild() override;

    virtual QString headersPrefix(TimePrefixLanguage timePrefixLanguage) = 0;
    virtual QString commitPrefix() = 0;

private:
    ExcelFile *currentSession;
    ExcelFile *currentDay;

    void finalPush(ExcelFile *excelFile);
    void appendToBuffers(QString message, bool addToCurrentDay = true);

};
Q_DECLARE_OPERATORS_FOR_FLAGS(Excel::HeaderMode)

#endif // EXCEL_H
