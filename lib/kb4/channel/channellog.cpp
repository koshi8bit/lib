#include "channellog.h"

ChannelLog::ChannelLog(QString name, QStringList *path, QObject *parent)
{
    QString seporator = "/";
    _logName = QString("%1%2%3")
            .arg(path->join(seporator))
            .arg(seporator)
            .arg(name);

    _plotName = _logName;
    _widgetName = name;

}
