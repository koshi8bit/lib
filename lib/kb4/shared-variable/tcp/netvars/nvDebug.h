#ifndef NVDEBUG_H
#define NVDEBUG_H

#include <QDebug>
#include <QFile>
#define NETVARSINFO "NetVars INFO:"


//#ifdef K8B_LIB_SHARED_VARIABLE_ENABLE_NVDEBUG
    #define nvDebug qDebug() << NETVARSINFO
//#else
//#endif

#endif // NVDEBUG_H
