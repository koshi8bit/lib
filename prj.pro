#-------------------------------------------------
#
# Project created by QtCreator 2018-12-04T15:58:02
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prj
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ui\rtplotwithlegend\axisconfig.cpp \
    ui\rtplotwithlegend\graph.cpp \
    ui\rtplotwithlegend\graphlegenditem.cpp \
    ui\rtplotwithlegend\rtplotwithlegend.cpp \
    ui\qcustomplot.cpp \
    ui\colorsetter.cpp \
    ui\scientificnotationedit.cpp \


HEADERS += \
    mainwindow.h \
    ui\rtplotwithlegend\axisconfig.h \
    ui\rtplotwithlegend\graph.h \
    ui\rtplotwithlegend\graphlegenditem.h \
    ui\rtplotwithlegend\rtplotwithlegend.h \
    ui\qcustomplot.h \
    ui\colorsetter.h \
    ui\scientificnotationedit.h \

FORMS += \
        mainwindow.ui \
    ui\rtplotwithlegend\axisconfig.ui \
    ui\rtplotwithlegend\rtplotwithlegend.ui \
    ui/graphlegenditem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
