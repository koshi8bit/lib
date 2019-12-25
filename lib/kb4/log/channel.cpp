#include "channel.h"

const QString Channel::seporator = "/";



Channel::Channel(QString name, QString postfix, QObject *parent)
    : Channel(name, name, postfix, parent)
{
    _logName = name;
}

Channel::Channel(QString name, QString postfix, QStringList &path, QObject *parent)
  : Channel(name, name, postfix, parent)
{
    //path << name;
    //_logName = path.join(seporator);

    _logName = QString("%1%2%3")
            .arg(path.join(seporator))
            .arg(seporator)
            .arg(name);
}

Channel::Channel(QString plotName, QString widgetName, QString postfix, QObject *parent)
    : QObject(parent)
{
    _plotName = plotName;
    _widgetName = widgetName;
    _postfix = postfix;
}

void Channel::setPostfix(const QString &postfix)
{
    _postfix = postfix;
}

QColor Channel::color() const
{
    return _color;
}

void Channel::setColor(const QColor &color)
{
    _color = color;
}


QString Channel::plotName() const
{
    return _plotName;
}

void Channel::setPlotName(const QString plotName)
{
    _plotName = plotName;
}

QString Channel::widgetName() const
{
    return _widgetName;
}

void Channel::setWidgetName(const QString widgetName)
{
    _widgetName = widgetName;
}

QString Channel::logName() const
{
    return _logName;
}

void Channel::setLogName(const QString logName)
{
    _logName = logName;
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

