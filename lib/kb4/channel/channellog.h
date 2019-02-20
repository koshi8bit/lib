#ifndef CHANNELLOG_H
#define CHANNELLOG_H

#include "channelt.h"

class ChannelLog
{
public:
    explicit ChannelLog(QString name, QStringList *path, QObject *parent = nullptr);

    QString plotName() const;
    QString widgetName() const;
    QString logName() const;

    void setPlotName(const QString &plotName);
    void setWidgetName(const QString &widgetName);

private:
    QString _plotName;
    QString _widgetName;
    QString _logName;

};

#endif // CHANNELLOG_H
