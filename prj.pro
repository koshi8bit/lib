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
    lib\qcustomplot\qcustomplot.cpp \
    lib\kb4\ui\axisconfig.cpp \
    lib\kb4\ui\colorsetter.cpp \
    lib\kb4\ui\scientificnotationedit.cpp \
    lib\kb4\ui\rtplotwithlegend.cpp \
    lib\kb4\ui\graph.cpp \
    lib\kb4\ui/graphlegenditem.cpp

HEADERS += \
    mainwindow.h \
    lib\qcustomplot\qcustomplot.h \
    lib\kb4\ui\axisconfig.h \
    lib\kb4\ui\colorsetter.h \
    lib\kb4\ui\scientificnotationedit.h \
    lib\kb4\ui\rtplotwithlegend.h \
    lib\kb4\ui\graph.h \
    lib\kb4\ui/graphlegenditem.h

FORMS += \
        mainwindow.ui \
    lib\kb4\ui\axisconfig.ui \
    lib\kb4\ui\rtplotwithlegend.ui \
    lib\kb4\ui/graphlegenditem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
