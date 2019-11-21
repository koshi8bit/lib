#include "channel.h"

Channel::Channel(QString name, QString postfix, QStringList *path, QObject *parent) : QObject(parent)
{
    QString seporator = "/";
    _logName = QString("%1%2%3")
            .arg(path->join(seporator))
            .arg(seporator)
            .arg(name);

    _plotName = _logName;
    _widgetName = name;

    _postfix = postfix;
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

void Channel::setWidgetName(const QString &widgetName)
{
    _widgetName = widgetName;
}

void Channel::_errorOccurred(QString message)
{
    qWarning() << message;
    emit errorOccurred(message);
}

QString Channel::postfix() const
{
    return _postfix;
}
