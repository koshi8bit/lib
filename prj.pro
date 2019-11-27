#-------------------------------------------------
#
# Project created by QtCreator 2018-12-04T15:58:02
#
#-------------------------------------------------

#QT       += core gui printsupport network
#INCLUDEPATH += ./

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = prj
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ./

CONFIG += c++11


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    lib/kb4/ui/gradientlineedit/minmax.ui \
    lib/kb4/ui/rtplotwithlegend/axis2/rtplotwithlegend.ui \
    lib/kb4/ui/rtplotwithlegend/axisconfig.ui \
    lib/kb4/ui/rtplotwithlegend/graphlegenditem.ui \
    mainwindow.ui \
    progressbar.ui

HEADERS += \
    lib/kb4/easyliving.h \
    lib/kb4/errorhandler/errorhandler.h \
    lib/kb4/log/channel.h \
    lib/kb4/log/channeldouble.h \
    lib/kb4/log/channelt.h \
    lib/kb4/log/excel/excel.h \
    lib/kb4/log/excel/excelfile.h \
    lib/kb4/log/excel/timelog/timelog.h \
    lib/kb4/log/log.h \
    lib/kb4/log/sql/sql.h \
    lib/kb4/qdebuglogger/qdebuglogger.h \
    lib/kb4/shared-variable/tcp/netvars.h \
    lib/kb4/shared-variable/tcp/netvars/initnvclient.h \
    lib/kb4/shared-variable/tcp/netvars/initnvserver.h \
    lib/kb4/shared-variable/tcp/netvars/netclient.h \
    lib/kb4/shared-variable/tcp/netvars/netvar.h \
    lib/kb4/shared-variable/tcp/netvars/netvarbase.h \
    lib/kb4/shared-variable/tcp/netvars/nvDebug.h \
    lib/kb4/shared-variable/tcp/netvars/varscontainer.h \
    lib/kb4/shared-variable/udp/shared-variable.h \
    lib/kb4/ui/gradientlineedit/gradientlineedit.h \
    lib/kb4/ui/gradientlineedit/minmax.h \
    lib/kb4/ui/rtplotwithlegend/axis2/rtplotwithlegend.h \
    lib/kb4/ui/rtplotwithlegend/axisconfig.h \
    lib/kb4/ui/rtplotwithlegend/colorsetter.h \
    lib/kb4/ui/rtplotwithlegend/graph.h \
    lib/kb4/ui/rtplotwithlegend/graphlegenditem.h \
    lib/kb4/ui/scientificnotationedit/scientificnotationedit.h \
    lib/qcustomplot/qcustomplot.h \
    mainwindow.h

SOURCES += \
    lib/kb4/easyliving.cpp \
    lib/kb4/errorhandler/errorhandler.cpp \
    lib/kb4/log/channel.cpp \
    lib/kb4/log/channeldouble.cpp \
    lib/kb4/log/excel/excel.cpp \
    lib/kb4/log/excel/excelfile.cpp \
    lib/kb4/log/excel/timelog/timelog.cpp \
    lib/kb4/log/log.cpp \
    lib/kb4/log/sql/sql.cpp \
    lib/kb4/qdebuglogger/qdebuglogger.cpp \
    lib/kb4/shared-variable/tcp/netvars/initnvclient.cpp \
    lib/kb4/shared-variable/tcp/netvars/initnvserver.cpp \
    lib/kb4/shared-variable/tcp/netvars/netclient.cpp \
    lib/kb4/shared-variable/tcp/netvars/netvar.cpp \
    lib/kb4/shared-variable/tcp/netvars/netvarbase.cpp \
    lib/kb4/shared-variable/tcp/netvars/varscontainer.cpp \
    lib/kb4/shared-variable/udp/shared-variable.cpp \
    lib/kb4/ui/gradientlineedit/gradientlineedit.cpp \
    lib/kb4/ui/gradientlineedit/minmax.cpp \
    lib/kb4/ui/rtplotwithlegend/axis2/rtplotwithlegend.cpp \
    lib/kb4/ui/rtplotwithlegend/axisconfig.cpp \
    lib/kb4/ui/rtplotwithlegend/colorsetter.cpp \
    lib/kb4/ui/rtplotwithlegend/graph.cpp \
    lib/kb4/ui/rtplotwithlegend/graphlegenditem.cpp \
    lib/kb4/ui/scientificnotationedit/scientificnotationedit.cpp \
    lib/qcustomplot/qcustomplot.cpp \
    main.cpp \
    mainwindow.cpp

DISTFILES += \
    lib/kb4/shared-variable/tcp/netvars/example/example.7z

RESOURCES += \
    ui-res.qrc

