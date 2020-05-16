#-------------------------------------------------
#
# Project created by QtCreator 2018-12-04T15:58:02
#
#-------------------------------------------------

QT       += core gui printsupport network
INCLUDEPATH += ./


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prj
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature raof Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += K8B_LIB_CHANNELS_SHOW_SV_CREATED

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


CONFIG += c++11


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

###################################################

RESOURCES += \
    lib/kb4/pic/ui-res.qrc

DISTFILES += \
    README.md \
    lib/kb4/pic/ico/about.png \
    lib/kb4/pic/ico/add--v2.png \
    lib/kb4/pic/ico/add--v2_002.png \
    lib/kb4/pic/ico/add.png \
    lib/kb4/pic/ico/alpha.png \
    lib/kb4/pic/ico/ask-question.png \
    lib/kb4/pic/ico/beta.png \
    lib/kb4/pic/ico/camera.png \
    lib/kb4/pic/ico/cancel.png \
    lib/kb4/pic/ico/checked.png \
    lib/kb4/pic/ico/checkmark.png \
    lib/kb4/pic/ico/document.png \
    lib/kb4/pic/ico/double-tick.png \
    lib/kb4/pic/ico/error.png \
    lib/kb4/pic/ico/folder-invoices.png \
    lib/kb4/pic/ico/gamma.png \
    lib/kb4/pic/ico/invisible.png \
    lib/kb4/pic/ico/invisible_002.png \
    lib/kb4/pic/ico/lock--v1.png \
    lib/kb4/pic/ico/login-rounded-right.png \
    lib/kb4/pic/ico/logout-rounded.png \
    lib/kb4/pic/ico/maintenance.png \
    lib/kb4/pic/ico/minus.png \
    lib/kb4/pic/ico/minus_002.png \
    lib/kb4/pic/ico/offline.png \
    lib/kb4/pic/ico/online.png \
    lib/kb4/pic/ico/opened-folder.png \
    lib/kb4/pic/ico/print.png \
    lib/kb4/pic/ico/radio-active.png \
    lib/kb4/pic/ico/readme.md \
    lib/kb4/pic/ico/save-all.png \
    lib/kb4/pic/ico/save-as.png \
    lib/kb4/pic/ico/save-close.png \
    lib/kb4/pic/ico/save.png \
    lib/kb4/pic/ico/screenshot.png \
    lib/kb4/pic/ico/terms-and-conditions.png \
    lib/kb4/pic/ico/toggle-off.png \
    lib/kb4/pic/ico/toggle-on.png \
    lib/kb4/pic/ico/unlock.png \
    lib/kb4/pic/ico/upload.png \
    lib/kb4/pic/ico/visible.png \
    lib/kb4/pic/ico/visible_002.png \
    lib/kb4/pic/ico/window-cloud.png \
    lib/kb4/pic/ico/window-settings.png \
    lib/kb4/pic/ui-gradientlineedit-gears.png \
    lib/kb4/pic/ui-realtimeqcp-cursor01.PNG \
    lib/kb4/pic/ui-realtimeqcp-cursor0102 — копия.PNG \
    lib/kb4/pic/ui-realtimeqcp-cursor0102.PNG \
    lib/kb4/pic/ui-realtimeqcp-mouse-area.PNG \
    lib/kb4/pic/ui-realtimeqcp-realtime.PNG \
    lib/kb4/pic/ui-realtimeqcp.PNG \
    lib/kb4/shared-variable/tcp/netvars/example/example.7z \
    lib/kb4/ui/plots/base/base.7z \
    lib/kb4/ui/qcustomplot/qcustomplot-original.7z \
    lib/update-kb4.bat \
    readme-pic/gradientlineedit01.png \
    readme-pic/realtimeqcp01.png \
    readme-pic/realtimeqcp02--.png \
    readme-pic/realtimeqcp03-.png \
    readme-pic/realtimeqcp04.png \
    readme-pic/valuedouble01.png

FORMS += \
    lib/kb4/ui/gradientlineedit/minmax.ui \
    lib/kb4/ui/plots/base/abstractplot.ui \
    lib/kb4/ui/plots/base/axisvalueconfig.ui \
    lib/kb4/ui/plots/base/graphlegenditem.ui \
    lib/kb4/ui/plots/realtime/axistimeconfig.ui \
    lib/kb4/ui/value/double/valuedouble.ui \
    mainwindow.ui \
    progressbar.ui

HEADERS += \
    lib/kb4/easyliving.h \
    lib/kb4/errorhandler/errorhandler.h \
    lib/kb4/log/channel.h \
    lib/kb4/log/channelbool.h \
    lib/kb4/log/channeldouble.h \
    lib/kb4/log/channelqstring.h \
    lib/kb4/log/channelrealtimegraph.h \
    lib/kb4/log/channelt.h \
    lib/kb4/log/excel/excel.h \
    lib/kb4/log/excel/excelfile.h \
    lib/kb4/log/excel/excelsimple.h \
    lib/kb4/log/excel/timelog/timelog.h \
    lib/kb4/log/log.h \
    lib/kb4/log/simple/simplelog.h \
    lib/kb4/log/sql/sql.h \
    lib/kb4/qdebuglogger/qdebuglogger.h \
    lib/kb4/settings/settings.h \
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
    lib/kb4/ui/label/qlabelext.h \
    lib/kb4/ui/plots/base/abstractgraph.h \
    lib/kb4/ui/plots/base/abstractplot.h \
    lib/kb4/ui/plots/base/axisvalueconfig.h \
    lib/kb4/ui/plots/base/colorsetter.h \
    lib/kb4/ui/plots/base/graphlegenditem.h \
    lib/kb4/ui/plots/radar/radargraph.h \
    lib/kb4/ui/plots/radar/radarplot.h \
    lib/kb4/ui/plots/radar/radartemperature4graph.h \
    lib/kb4/ui/plots/radar/radartemperature4plot.h \
    lib/kb4/ui/plots/realtime/axistimeconfig.h \
    lib/kb4/ui/plots/realtime/realtimegraph.h \
    lib/kb4/ui/plots/realtime/realtimeplot.h \
    lib/kb4/ui/plots/simple/errorxygraph.h \
    lib/kb4/ui/plots/simple/errorygraph.h \
    lib/kb4/ui/plots/simple/simplegraph.h \
    lib/kb4/ui/plots/simple/simpleplot.h \
    lib/kb4/ui/printscreener/printscreener.h \
    lib/kb4/ui/qcustomplot/qcustomplot.h \
    lib/kb4/ui/scientificnotationedit/scientificnotationedit.h \
    lib/kb4/ui/value/double/valuedouble.h \
    lib/kb4/worker/worker.h \
    mainwindow.h

SOURCES += \
    lib/kb4/easyliving.cpp \
    lib/kb4/errorhandler/errorhandler.cpp \
    lib/kb4/log/channel.cpp \
    lib/kb4/log/channelbool.cpp \
    lib/kb4/log/channeldouble.cpp \
    lib/kb4/log/channelqstring.cpp \
    lib/kb4/log/excel/excel.cpp \
    lib/kb4/log/excel/excelfile.cpp \
    lib/kb4/log/excel/excelsimple.cpp \
    lib/kb4/log/excel/timelog/timelog.cpp \
    lib/kb4/log/log.cpp \
    lib/kb4/log/simple/simplelog.cpp \
    lib/kb4/log/sql/sql.cpp \
    lib/kb4/qdebuglogger/qdebuglogger.cpp \
    lib/kb4/settings/settings.cpp \
    lib/kb4/shared-variable/tcp/netvars/initnvclient.cpp \
    lib/kb4/shared-variable/tcp/netvars/initnvserver.cpp \
    lib/kb4/shared-variable/tcp/netvars/netclient.cpp \
    lib/kb4/shared-variable/tcp/netvars/netvar.cpp \
    lib/kb4/shared-variable/tcp/netvars/netvarbase.cpp \
    lib/kb4/shared-variable/tcp/netvars/varscontainer.cpp \
    lib/kb4/shared-variable/udp/shared-variable.cpp \
    lib/kb4/ui/gradientlineedit/gradientlineedit.cpp \
    lib/kb4/ui/gradientlineedit/minmax.cpp \
    lib/kb4/ui/label/qlabelext.cpp \
    lib/kb4/ui/plots/base/abstractgraph.cpp \
    lib/kb4/ui/plots/base/abstractplot.cpp \
    lib/kb4/ui/plots/base/axisvalueconfig.cpp \
    lib/kb4/ui/plots/base/colorsetter.cpp \
    lib/kb4/ui/plots/base/graphlegenditem.cpp \
    lib/kb4/ui/plots/radar/radargraph.cpp \
    lib/kb4/ui/plots/radar/radarplot.cpp \
    lib/kb4/ui/plots/radar/radartemperature4graph.cpp \
    lib/kb4/ui/plots/radar/radartemperature4plot.cpp \
    lib/kb4/ui/plots/realtime/axistimeconfig.cpp \
    lib/kb4/ui/plots/realtime/realtimegraph.cpp \
    lib/kb4/ui/plots/realtime/realtimeplot.cpp \
    lib/kb4/ui/plots/simple/errorxygraph.cpp \
    lib/kb4/ui/plots/simple/errorygraph.cpp \
    lib/kb4/ui/plots/simple/simplegraph.cpp \
    lib/kb4/ui/plots/simple/simpleplot.cpp \
    lib/kb4/ui/printscreener/printscreener.cpp \
    lib/kb4/ui/qcustomplot/qcustomplot.cpp \
    lib/kb4/ui/scientificnotationedit/scientificnotationedit.cpp \
    lib/kb4/ui/value/double/valuedouble.cpp \
    lib/kb4/worker/worker.cpp \
    main.cpp \
    mainwindow.cpp
