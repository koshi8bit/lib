#ifndef EXCEL_H
#define EXCEL_H

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QDir>

#include <lib/kb4/log/log.h>
#include <lib/kb4/channel/channelt.h>
#include <lib/kb4/macro.h>

#include "excelfile.h"


class Excel : public Log
{

public:
    enum HeaderModeFlag {
        NoHeader = 0x0000,
        PlotName = 0x0001,
        LogName = 0x0002,
        WidgetName = 0x0004
    };
    Q_DECLARE_FLAGS(HeaderMode, HeaderModeFlag)

    Excel(QObject *parent = nullptr);
    ~Excel() override;

    void configure(QString path, HeaderMode headerMode);

    void push() override;
    void commit() override;

protected:
    static const QString elementDelimeter;
    static const QString lineDelimeter;
    static QString formatDoubleValue(double value);

    HeaderMode headerMode;
    void finishConfigureChild() override;

    virtual QString headersPrefix() = 0;
    virtual QString commitPrefix() = 0;

private:
    ExcelFile *currentSession;
    ExcelFile *currentDay;

    void finalPush(ExcelFile *excelFile);
    void appendToBuffers(QString message, bool addToCurrentDay = true);

    void configureHeader();
    void generateHeaderLine(HeaderModeFlag flag);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Excel::HeaderMode)

#endif // EXCEL_H
