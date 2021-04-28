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
    lib/kb4/lib.qrc \
    lib/kb4/pic/ui-res.qrc

DISTFILES += \
    lib/kb4/pic/ico/clean-web.bat \
    lib/kb4/pic/ico/custom/ask-question_002.png \
    lib/kb4/pic/ico/custom/gears-white.png \
    lib/kb4/pic/ico/custom/gears.png \
    lib/kb4/pic/ico/custom/gears2.png \
    lib/kb4/pic/ico/readme.md \
    lib/kb4/pic/ico/web/about.png \
    lib/kb4/pic/ico/web/add--v2.png \
    lib/kb4/pic/ico/web/add-link.png \
    lib/kb4/pic/ico/web/add-link_002.png \
    lib/kb4/pic/ico/web/add-tag.png \
    lib/kb4/pic/ico/web/alpha.png \
    lib/kb4/pic/ico/web/alpha_002.png \
    lib/kb4/pic/ico/web/ask-question.png \
    lib/kb4/pic/ico/web/ask-question_002.png \
    lib/kb4/pic/ico/web/ask-question_003.png \
    lib/kb4/pic/ico/web/attach.png \
    lib/kb4/pic/ico/web/attach_002.png \
    lib/kb4/pic/ico/web/beta.png \
    lib/kb4/pic/ico/web/beta_002.png \
    lib/kb4/pic/ico/web/bookmark-ribbon.png \
    lib/kb4/pic/ico/web/broken-link.png \
    lib/kb4/pic/ico/web/broken-link_002.png \
    lib/kb4/pic/ico/web/camera.png \
    lib/kb4/pic/ico/web/cancel.png \
    lib/kb4/pic/ico/web/checked.png \
    lib/kb4/pic/ico/web/checkmark.png \
    lib/kb4/pic/ico/web/contact-card.png \
    lib/kb4/pic/ico/web/delete-link.png \
    lib/kb4/pic/ico/web/delete-link_002.png \
    lib/kb4/pic/ico/web/delta.png \
    lib/kb4/pic/ico/web/do-not-disturb.png \
    lib/kb4/pic/ico/web/do-not-disturb_002.png \
    lib/kb4/pic/ico/web/document.png \
    lib/kb4/pic/ico/web/double-tick.png \
    lib/kb4/pic/ico/web/edit-link.png \
    lib/kb4/pic/ico/web/eppendorf.png \
    lib/kb4/pic/ico/web/epsilon.png \
    lib/kb4/pic/ico/web/equal-sign.png \
    lib/kb4/pic/ico/web/error.png \
    lib/kb4/pic/ico/web/eta.png \
    lib/kb4/pic/ico/web/expired.png \
    lib/kb4/pic/ico/web/filled-trash.png \
    lib/kb4/pic/ico/web/filled-trash_002.png \
    lib/kb4/pic/ico/web/flip-horizontal.png \
    lib/kb4/pic/ico/web/flip-vertical.png \
    lib/kb4/pic/ico/web/folder-invoices.png \
    lib/kb4/pic/ico/web/full-trash.png \
    lib/kb4/pic/ico/web/gamma.png \
    lib/kb4/pic/ico/web/gamma_002.png \
    lib/kb4/pic/ico/web/gears.png \
    lib/kb4/pic/ico/web/ground-symbol.png \
    lib/kb4/pic/ico/web/idea.png \
    lib/kb4/pic/ico/web/infinity.png \
    lib/kb4/pic/ico/web/information.png \
    lib/kb4/pic/ico/web/invisible.png \
    lib/kb4/pic/ico/web/invisible_002.png \
    lib/kb4/pic/ico/web/iota-letter.png \
    lib/kb4/pic/ico/web/kappa.png \
    lib/kb4/pic/ico/web/key.png \
    lib/kb4/pic/ico/web/ksi--v1.png \
    lib/kb4/pic/ico/web/ksi.png \
    lib/kb4/pic/ico/web/lambda.png \
    lib/kb4/pic/ico/web/lambda_002.png \
    lib/kb4/pic/ico/web/like.png \
    lib/kb4/pic/ico/web/like_002.png \
    lib/kb4/pic/ico/web/link.png \
    lib/kb4/pic/ico/web/link_002.png \
    lib/kb4/pic/ico/web/lock--v1.png \
    lib/kb4/pic/ico/web/login-rounded-right.png \
    lib/kb4/pic/ico/web/logout-rounded.png \
    lib/kb4/pic/ico/web/maintenance.png \
    lib/kb4/pic/ico/web/messaging-.png \
    lib/kb4/pic/ico/web/microscope.png \
    lib/kb4/pic/ico/web/minus-math.png \
    lib/kb4/pic/ico/web/minus.png \
    lib/kb4/pic/ico/web/mu.png \
    lib/kb4/pic/ico/web/mu_002.png \
    lib/kb4/pic/ico/web/multiply.png \
    lib/kb4/pic/ico/web/no-reminders.png \
    lib/kb4/pic/ico/web/no-reminders_002.png \
    lib/kb4/pic/ico/web/not-equal.png \
    lib/kb4/pic/ico/web/nu.png \
    lib/kb4/pic/ico/web/ok.png \
    lib/kb4/pic/ico/web/omega.png \
    lib/kb4/pic/ico/web/omega_002.png \
    lib/kb4/pic/ico/web/omicron.png \
    lib/kb4/pic/ico/web/opened-folder.png \
    lib/kb4/pic/ico/web/phi.png \
    lib/kb4/pic/ico/web/pi.png \
    lib/kb4/pic/ico/web/pi_002.png \
    lib/kb4/pic/ico/web/plus-math.png \
    lib/kb4/pic/ico/web/print.png \
    lib/kb4/pic/ico/web/psi.png \
    lib/kb4/pic/ico/web/radio-active.png \
    lib/kb4/pic/ico/web/rho.png \
    lib/kb4/pic/ico/web/save-all.png \
    lib/kb4/pic/ico/web/save-as.png \
    lib/kb4/pic/ico/web/save-close.png \
    lib/kb4/pic/ico/web/save.png \
    lib/kb4/pic/ico/web/screenshot.png \
    lib/kb4/pic/ico/web/screenshot_002.png \
    lib/kb4/pic/ico/web/screenshot_003.png \
    lib/kb4/pic/ico/web/screenshot_004.png \
    lib/kb4/pic/ico/web/services.png \
    lib/kb4/pic/ico/web/settings.png \
    lib/kb4/pic/ico/web/sigma.png \
    lib/kb4/pic/ico/web/sigma_002.png \
    lib/kb4/pic/ico/web/sos.png \
    lib/kb4/pic/ico/web/sos_002.png \
    lib/kb4/pic/ico/web/star.png \
    lib/kb4/pic/ico/web/star_002.png \
    lib/kb4/pic/ico/web/support.png \
    lib/kb4/pic/ico/web/tau.png \
    lib/kb4/pic/ico/web/terms-and-conditions.png \
    lib/kb4/pic/ico/web/test-tube.png \
    lib/kb4/pic/ico/web/theta.png \
    lib/kb4/pic/ico/web/thin-test-tube.png \
    lib/kb4/pic/ico/web/toggle-off.png \
    lib/kb4/pic/ico/web/toggle-on.png \
    lib/kb4/pic/ico/web/translation.png \
    lib/kb4/pic/ico/web/unlock.png \
    lib/kb4/pic/ico/web/upload.png \
    lib/kb4/pic/ico/web/visible.png \
    lib/kb4/pic/ico/web/visible_002.png \
    lib/kb4/pic/ico/web/xi.png \
    lib/kb4/pic/ico/web/zeta.png \
    lib/kb4/pic/ico/web/zoom-in.png \
    lib/kb4/pic/ico/web/zoom-out.png \
    lib/kb4/pic/ico/web/zoom-to-actual-size.png \
    lib/kb4/pic/ico/web/zoom-to-extents.png \
    lib/kb4/pic/paint.png \
    lib/kb4/pic/ui-gradientlineedit-gears.png \
    lib/kb4/pic/ui-plot-axis-value-01.png \
    lib/kb4/pic/ui-plot-axis-value-02.png \
    lib/kb4/pic/ui-plot-axis-value-03.png \
    lib/kb4/pic/ui-realtimeqcp-cursor01.PNG \
    lib/kb4/pic/ui-realtimeqcp-cursor0102 — копия.PNG \
    lib/kb4/pic/ui-realtimeqcp-cursor0102.PNG \
    lib/kb4/pic/ui-realtimeqcp-mouse-area.PNG \
    lib/kb4/pic/ui-realtimeqcp-realtime.PNG \
    lib/kb4/pic/ui-realtimeqcp.PNG \
    lib/kb4/shared-variable/tcp/netvars/example/example.7z \
    lib/kb4/ui/faults/template.html \
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
    lib/kb4/ui/faults/fault.h \
    lib/kb4/ui/faults/faultswidget.h \
    lib/kb4/ui/gradientlineedit/gradientlineedit.h \
    lib/kb4/ui/gradientlineedit/minmax.h \
    lib/kb4/ui/hotcolormap/hotspot.h \
    lib/kb4/ui/hotcolormap/hotspotmap.h \
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
    lib/kb4/ui/faults/fault.cpp \
    lib/kb4/ui/faults/faultswidget.cpp \
    lib/kb4/ui/gradientlineedit/gradientlineedit.cpp \
    lib/kb4/ui/gradientlineedit/minmax.cpp \
    lib/kb4/ui/hotcolormap/hotspot.cpp \
    lib/kb4/ui/hotcolormap/hotspotmap.cpp \
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
