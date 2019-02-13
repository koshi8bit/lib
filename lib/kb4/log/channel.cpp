#include "channel.h"

Channel::Channel(QString name, QStringList *path, QString postfix, QObject *parent) : QObject(parent)
{
    QString seporator = "/";
    _logName = QString("%1%2%3")
            .arg(path->join(seporator))
            .arg(seporator)
            .arg(name);

    _plotName = _logName;
    _postfix = postfix;

    _widgetName = name;
}

QString Channel::plotName() const
{
    return _plotName;
}

QString Channel::widgetName() const
{
    return _widgetName;
}

QString Channel::logName() const
{
    return _logName;
}

void Channel::setPlotName(const QString &plotName)
{
    _plotName = plotName;
}

QString Channel::postfix() const
{
    return _postfix;
}
