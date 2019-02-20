#include "channel.h"

Channel::Channel(QString postfix, QObject *parent) : QObject(parent)
{
    _postfix = postfix;
}

QString Channel::postfix() const
{
    return _postfix;
}
