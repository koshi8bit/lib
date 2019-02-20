#ifndef CHANNELLOGT_H
#define CHANNELLOGT_H

#include "channelt.h"
#include "channellog.h"

template <typename T>
class ChannelLogT : public ChannelT<T>, public ChannelLog
{
public:
    ChannelLogT(QString name, QString postfix, QStringList *path, QObject *parent)
        :ChannelLog(name, path, parent), ChannelT<T>(postfix, parent)
    {

    }
};

#endif // CHANNELLOGT_H
