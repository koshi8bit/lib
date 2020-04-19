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

RESOURCES += \
    lib/kb4/pic/ui-res.qrc

DISTFILES += \
    README.md \
    lib/kb4/pic/ico/016/icons8-about-16.png \
    lib/kb4/pic/ico/016/icons8-add-16-2.png \
    lib/kb4/pic/ico/016/icons8-add-16-3.png \
    lib/kb4/pic/ico/016/icons8-add-16.png \
    lib/kb4/pic/ico/016/icons8-ask-question-16.png \
    lib/kb4/pic/ico/016/icons8-cancel-16.png \
    lib/kb4/pic/ico/016/icons8-checked-16.png \
    lib/kb4/pic/ico/016/icons8-checkmark-16.png \
    lib/kb4/pic/ico/016/icons8-document-16.png \
    lib/kb4/pic/ico/016/icons8-double-tick-16.png \
    lib/kb4/pic/ico/016/icons8-error-16.png \
    lib/kb4/pic/ico/016/icons8-eye-16-2.png \
    lib/kb4/pic/ico/016/icons8-eye-16.png \
    lib/kb4/pic/ico/016/icons8-folder-16.png \
    lib/kb4/pic/ico/016/icons8-invisible-16-2.png \
    lib/kb4/pic/ico/016/icons8-invisible-16.png \
    lib/kb4/pic/ico/016/icons8-lock-16.png \
    lib/kb4/pic/ico/016/icons8-login-16.png \
    lib/kb4/pic/ico/016/icons8-maintenance-16.png \
    lib/kb4/pic/ico/016/icons8-minus-16-2.png \
    lib/kb4/pic/ico/016/icons8-minus-16.png \
    lib/kb4/pic/ico/016/icons8-offline-16.png \
    lib/kb4/pic/ico/016/icons8-online-16.png \
    lib/kb4/pic/ico/016/icons8-opened-folder-16.png \
    lib/kb4/pic/ico/016/icons8-padlock-16.png \
    lib/kb4/pic/ico/016/icons8-save-16.png \
    lib/kb4/pic/ico/016/icons8-save-all-16.png \
    lib/kb4/pic/ico/016/icons8-save-as-16.png \
    lib/kb4/pic/ico/016/icons8-save-close-16.png \
    lib/kb4/pic/ico/016/icons8-sign-out-16.png \
    lib/kb4/pic/ico/016/icons8-terms-and-conditions-16.png \
    lib/kb4/pic/ico/016/icons8-toggle-off-16.png \
    lib/kb4/pic/ico/016/icons8-toggle-on-16.png \
    lib/kb4/pic/ico/016/icons8-upload-16.png \
    lib/kb4/pic/ico/016/icons8-window-cloud-16.png \
    lib/kb4/pic/ico/016/icons8-window-settings-16.png \
    lib/kb4/pic/ico/020/icons8-about-20.png \
    lib/kb4/pic/ico/020/icons8-add-20-2.png \
    lib/kb4/pic/ico/020/icons8-add-20-3.png \
    lib/kb4/pic/ico/020/icons8-add-20.png \
    lib/kb4/pic/ico/020/icons8-ask-question-20.png \
    lib/kb4/pic/ico/020/icons8-cancel-20.png \
    lib/kb4/pic/ico/020/icons8-checked-20.png \
    lib/kb4/pic/ico/020/icons8-checkmark-20.png \
    lib/kb4/pic/ico/020/icons8-document-20.png \
    lib/kb4/pic/ico/020/icons8-double-tick-20.png \
    lib/kb4/pic/ico/020/icons8-error-20.png \
    lib/kb4/pic/ico/020/icons8-eye-20-2.png \
    lib/kb4/pic/ico/020/icons8-eye-20.png \
    lib/kb4/pic/ico/020/icons8-folder-20.png \
    lib/kb4/pic/ico/020/icons8-invisible-20-2.png \
    lib/kb4/pic/ico/020/icons8-invisible-20.png \
    lib/kb4/pic/ico/020/icons8-lock-20.png \
    lib/kb4/pic/ico/020/icons8-login-20.png \
    lib/kb4/pic/ico/020/icons8-maintenance-20.png \
    lib/kb4/pic/ico/020/icons8-minus-20-2.png \
    lib/kb4/pic/ico/020/icons8-minus-20.png \
    lib/kb4/pic/ico/020/icons8-offline-20.png \
    lib/kb4/pic/ico/020/icons8-online-20.png \
    lib/kb4/pic/ico/020/icons8-opened-folder-20.png \
    lib/kb4/pic/ico/020/icons8-padlock-20.png \
    lib/kb4/pic/ico/020/icons8-save-20.png \
    lib/kb4/pic/ico/020/icons8-save-all-20.png \
    lib/kb4/pic/ico/020/icons8-save-as-20.png \
    lib/kb4/pic/ico/020/icons8-save-close-20.png \
    lib/kb4/pic/ico/020/icons8-sign-out-20.png \
    lib/kb4/pic/ico/020/icons8-terms-and-conditions-20.png \
    lib/kb4/pic/ico/020/icons8-toggle-off-20.png \
    lib/kb4/pic/ico/020/icons8-toggle-on-20.png \
    lib/kb4/pic/ico/020/icons8-upload-20.png \
    lib/kb4/pic/ico/020/icons8-window-cloud-20.png \
    lib/kb4/pic/ico/020/icons8-window-settings-20.png \
    lib/kb4/pic/ico/032/icons8-about-32.png \
    lib/kb4/pic/ico/032/icons8-add-32-2.png \
    lib/kb4/pic/ico/032/icons8-add-32-3.png \
    lib/kb4/pic/ico/032/icons8-add-32.png \
    lib/kb4/pic/ico/032/icons8-ask-question-32.png \
    lib/kb4/pic/ico/032/icons8-cancel-32.png \
    lib/kb4/pic/ico/032/icons8-checked-32.png \
    lib/kb4/pic/ico/032/icons8-checkmark-32.png \
    lib/kb4/pic/ico/032/icons8-document-32.png \
    lib/kb4/pic/ico/032/icons8-double-tick-32.png \
    lib/kb4/pic/ico/032/icons8-error-32.png \
    lib/kb4/pic/ico/032/icons8-eye-32-2.png \
    lib/kb4/pic/ico/032/icons8-eye-32.png \
    lib/kb4/pic/ico/032/icons8-folder-32.png \
    lib/kb4/pic/ico/032/icons8-invisible-32-2.png \
    lib/kb4/pic/ico/032/icons8-invisible-32.png \
    lib/kb4/pic/ico/032/icons8-lock-32.png \
    lib/kb4/pic/ico/032/icons8-login-32.png \
    lib/kb4/pic/ico/032/icons8-maintenance-32.png \
    lib/kb4/pic/ico/032/icons8-minus-32-2.png \
    lib/kb4/pic/ico/032/icons8-minus-32.png \
    lib/kb4/pic/ico/032/icons8-offline-32.png \
    lib/kb4/pic/ico/032/icons8-online-32.png \
    lib/kb4/pic/ico/032/icons8-opened-folder-32.png \
    lib/kb4/pic/ico/032/icons8-padlock-32.png \
    lib/kb4/pic/ico/032/icons8-save-32.png \
    lib/kb4/pic/ico/032/icons8-save-all-32.png \
    lib/kb4/pic/ico/032/icons8-save-as-32.png \
    lib/kb4/pic/ico/032/icons8-save-close-32.png \
    lib/kb4/pic/ico/032/icons8-sign-out-32.png \
    lib/kb4/pic/ico/032/icons8-terms-and-conditions-32.png \
    lib/kb4/pic/ico/032/icons8-toggle-off-32.png \
    lib/kb4/pic/ico/032/icons8-toggle-on-32.png \
    lib/kb4/pic/ico/032/icons8-upload-32.png \
    lib/kb4/pic/ico/032/icons8-window-cloud-32.png \
    lib/kb4/pic/ico/032/icons8-window-settings-32.png \
    lib/kb4/pic/ico/035/icons8-about-35.png \
    lib/kb4/pic/ico/035/icons8-add-35-2.png \
    lib/kb4/pic/ico/035/icons8-add-35-3.png \
    lib/kb4/pic/ico/035/icons8-add-35.png \
    lib/kb4/pic/ico/035/icons8-ask-question-35.png \
    lib/kb4/pic/ico/035/icons8-cancel-35.png \
    lib/kb4/pic/ico/035/icons8-checked-35.png \
    lib/kb4/pic/ico/035/icons8-checkmark-35.png \
    lib/kb4/pic/ico/035/icons8-document-35.png \
    lib/kb4/pic/ico/035/icons8-double-tick-35.png \
    lib/kb4/pic/ico/035/icons8-error-35.png \
    lib/kb4/pic/ico/035/icons8-eye-35-2.png \
    lib/kb4/pic/ico/035/icons8-eye-35.png \
    lib/kb4/pic/ico/035/icons8-folder-35.png \
    lib/kb4/pic/ico/035/icons8-invisible-35-2.png \
    lib/kb4/pic/ico/035/icons8-invisible-35.png \
    lib/kb4/pic/ico/035/icons8-lock-35.png \
    lib/kb4/pic/ico/035/icons8-login-35.png \
    lib/kb4/pic/ico/035/icons8-maintenance-35.png \
    lib/kb4/pic/ico/035/icons8-minus-35-2.png \
    lib/kb4/pic/ico/035/icons8-minus-35.png \
    lib/kb4/pic/ico/035/icons8-offline-35.png \
    lib/kb4/pic/ico/035/icons8-online-35.png \
    lib/kb4/pic/ico/035/icons8-opened-folder-35.png \
    lib/kb4/pic/ico/035/icons8-padlock-35.png \
    lib/kb4/pic/ico/035/icons8-save-35.png \
    lib/kb4/pic/ico/035/icons8-save-all-35.png \
    lib/kb4/pic/ico/035/icons8-save-as-35.png \
    lib/kb4/pic/ico/035/icons8-save-close-35.png \
    lib/kb4/pic/ico/035/icons8-sign-out-35.png \
    lib/kb4/pic/ico/035/icons8-terms-and-conditions-35.png \
    lib/kb4/pic/ico/035/icons8-toggle-off-35.png \
    lib/kb4/pic/ico/035/icons8-toggle-on-35.png \
    lib/kb4/pic/ico/035/icons8-upload-35.png \
    lib/kb4/pic/ico/035/icons8-window-cloud-35.png \
    lib/kb4/pic/ico/035/icons8-window-settings-35.png \
    lib/kb4/pic/ico/048/icons8-about-48.png \
    lib/kb4/pic/ico/048/icons8-add-48-2.png \
    lib/kb4/pic/ico/048/icons8-add-48-3.png \
    lib/kb4/pic/ico/048/icons8-add-48.png \
    lib/kb4/pic/ico/048/icons8-ask-question-48.png \
    lib/kb4/pic/ico/048/icons8-cancel-48.png \
    lib/kb4/pic/ico/048/icons8-checked-48.png \
    lib/kb4/pic/ico/048/icons8-checkmark-48.png \
    lib/kb4/pic/ico/048/icons8-document-48.png \
    lib/kb4/pic/ico/048/icons8-double-tick-48.png \
    lib/kb4/pic/ico/048/icons8-error-48.png \
    lib/kb4/pic/ico/048/icons8-eye-48-2.png \
    lib/kb4/pic/ico/048/icons8-eye-48.png \
    lib/kb4/pic/ico/048/icons8-folder-48.png \
    lib/kb4/pic/ico/048/icons8-invisible-48-2.png \
    lib/kb4/pic/ico/048/icons8-invisible-48.png \
    lib/kb4/pic/ico/048/icons8-lock-48.png \
    lib/kb4/pic/ico/048/icons8-login-48.png \
    lib/kb4/pic/ico/048/icons8-maintenance-48.png \
    lib/kb4/pic/ico/048/icons8-minus-48-2.png \
    lib/kb4/pic/ico/048/icons8-minus-48.png \
    lib/kb4/pic/ico/048/icons8-offline-48.png \
    lib/kb4/pic/ico/048/icons8-online-48.png \
    lib/kb4/pic/ico/048/icons8-opened-folder-48.png \
    lib/kb4/pic/ico/048/icons8-padlock-48.png \
    lib/kb4/pic/ico/048/icons8-save-48.png \
    lib/kb4/pic/ico/048/icons8-save-all-48.png \
    lib/kb4/pic/ico/048/icons8-save-as-48.png \
    lib/kb4/pic/ico/048/icons8-save-close-48.png \
    lib/kb4/pic/ico/048/icons8-sign-out-48.png \
    lib/kb4/pic/ico/048/icons8-terms-and-conditions-48.png \
    lib/kb4/pic/ico/048/icons8-toggle-off-48.png \
    lib/kb4/pic/ico/048/icons8-toggle-on-48.png \
    lib/kb4/pic/ico/048/icons8-upload-48.png \
    lib/kb4/pic/ico/048/icons8-window-cloud-48.png \
    lib/kb4/pic/ico/048/icons8-window-settings-48.png \
    lib/kb4/pic/ico/050/icons8-about-50.png \
    lib/kb4/pic/ico/050/icons8-add-50-2.png \
    lib/kb4/pic/ico/050/icons8-add-50-3.png \
    lib/kb4/pic/ico/050/icons8-add-50.png \
    lib/kb4/pic/ico/050/icons8-ask-question-50.png \
    lib/kb4/pic/ico/050/icons8-cancel-50.png \
    lib/kb4/pic/ico/050/icons8-checked-50.png \
    lib/kb4/pic/ico/050/icons8-checkmark-50.png \
    lib/kb4/pic/ico/050/icons8-document-50.png \
    lib/kb4/pic/ico/050/icons8-double-tick-50.png \
    lib/kb4/pic/ico/050/icons8-error-50.png \
    lib/kb4/pic/ico/050/icons8-eye-50-2.png \
    lib/kb4/pic/ico/050/icons8-eye-50.png \
    lib/kb4/pic/ico/050/icons8-folder-50.png \
    lib/kb4/pic/ico/050/icons8-invisible-50-2.png \
    lib/kb4/pic/ico/050/icons8-invisible-50.png \
    lib/kb4/pic/ico/050/icons8-lock-50.png \
    lib/kb4/pic/ico/050/icons8-login-50.png \
    lib/kb4/pic/ico/050/icons8-maintenance-50.png \
    lib/kb4/pic/ico/050/icons8-minus-50-2.png \
    lib/kb4/pic/ico/050/icons8-minus-50.png \
    lib/kb4/pic/ico/050/icons8-offline-50.png \
    lib/kb4/pic/ico/050/icons8-online-50.png \
    lib/kb4/pic/ico/050/icons8-opened-folder-50.png \
    lib/kb4/pic/ico/050/icons8-padlock-50.png \
    lib/kb4/pic/ico/050/icons8-save-50.png \
    lib/kb4/pic/ico/050/icons8-save-all-50.png \
    lib/kb4/pic/ico/050/icons8-save-as-50.png \
    lib/kb4/pic/ico/050/icons8-save-close-50.png \
    lib/kb4/pic/ico/050/icons8-sign-out-50.png \
    lib/kb4/pic/ico/050/icons8-terms-and-conditions-50.png \
    lib/kb4/pic/ico/050/icons8-toggle-off-50.png \
    lib/kb4/pic/ico/050/icons8-toggle-on-50.png \
    lib/kb4/pic/ico/050/icons8-upload-50.png \
    lib/kb4/pic/ico/050/icons8-window-cloud-50.png \
    lib/kb4/pic/ico/050/icons8-window-settings-50.png \
    lib/kb4/pic/ico/064/icons8-about-64.png \
    lib/kb4/pic/ico/064/icons8-add-64-2.png \
    lib/kb4/pic/ico/064/icons8-add-64-3.png \
    lib/kb4/pic/ico/064/icons8-add-64.png \
    lib/kb4/pic/ico/064/icons8-ask-question-64.png \
    lib/kb4/pic/ico/064/icons8-cancel-64.png \
    lib/kb4/pic/ico/064/icons8-checked-64.png \
    lib/kb4/pic/ico/064/icons8-checkmark-64.png \
    lib/kb4/pic/ico/064/icons8-document-64.png \
    lib/kb4/pic/ico/064/icons8-double-tick-64.png \
    lib/kb4/pic/ico/064/icons8-error-64.png \
    lib/kb4/pic/ico/064/icons8-eye-64-2.png \
    lib/kb4/pic/ico/064/icons8-eye-64.png \
    lib/kb4/pic/ico/064/icons8-folder-64.png \
    lib/kb4/pic/ico/064/icons8-invisible-64-2.png \
    lib/kb4/pic/ico/064/icons8-invisible-64.png \
    lib/kb4/pic/ico/064/icons8-lock-64.png \
    lib/kb4/pic/ico/064/icons8-login-64.png \
    lib/kb4/pic/ico/064/icons8-maintenance-64.png \
    lib/kb4/pic/ico/064/icons8-minus-64-2.png \
    lib/kb4/pic/ico/064/icons8-minus-64.png \
    lib/kb4/pic/ico/064/icons8-offline-64.png \
    lib/kb4/pic/ico/064/icons8-online-64.png \
    lib/kb4/pic/ico/064/icons8-opened-folder-64.png \
    lib/kb4/pic/ico/064/icons8-padlock-64.png \
    lib/kb4/pic/ico/064/icons8-save-64.png \
    lib/kb4/pic/ico/064/icons8-save-all-64.png \
    lib/kb4/pic/ico/064/icons8-save-as-64.png \
    lib/kb4/pic/ico/064/icons8-save-close-64.png \
    lib/kb4/pic/ico/064/icons8-sign-out-64.png \
    lib/kb4/pic/ico/064/icons8-terms-and-conditions-64.png \
    lib/kb4/pic/ico/064/icons8-toggle-off-64.png \
    lib/kb4/pic/ico/064/icons8-toggle-on-64.png \
    lib/kb4/pic/ico/064/icons8-upload-64.png \
    lib/kb4/pic/ico/064/icons8-window-cloud-64.png \
    lib/kb4/pic/ico/064/icons8-window-settings-64.png \
    lib/kb4/pic/ico/100/icons8-about-100.png \
    lib/kb4/pic/ico/100/icons8-add-100-2.png \
    lib/kb4/pic/ico/100/icons8-add-100-3.png \
    lib/kb4/pic/ico/100/icons8-add-100.png \
    lib/kb4/pic/ico/100/icons8-ask-question-100.png \
    lib/kb4/pic/ico/100/icons8-cancel-100.png \
    lib/kb4/pic/ico/100/icons8-checked-100.png \
    lib/kb4/pic/ico/100/icons8-checkmark-100.png \
    lib/kb4/pic/ico/100/icons8-document-100.png \
    lib/kb4/pic/ico/100/icons8-double-tick-100.png \
    lib/kb4/pic/ico/100/icons8-error-100.png \
    lib/kb4/pic/ico/100/icons8-eye-100-2.png \
    lib/kb4/pic/ico/100/icons8-eye-100.png \
    lib/kb4/pic/ico/100/icons8-folder-100.png \
    lib/kb4/pic/ico/100/icons8-invisible-100-2.png \
    lib/kb4/pic/ico/100/icons8-invisible-100.png \
    lib/kb4/pic/ico/100/icons8-lock-100.png \
    lib/kb4/pic/ico/100/icons8-login-100.png \
    lib/kb4/pic/ico/100/icons8-maintenance-100.png \
    lib/kb4/pic/ico/100/icons8-minus-100-2.png \
    lib/kb4/pic/ico/100/icons8-minus-100.png \
    lib/kb4/pic/ico/100/icons8-offline-100.png \
    lib/kb4/pic/ico/100/icons8-online-100.png \
    lib/kb4/pic/ico/100/icons8-opened-folder-100.png \
    lib/kb4/pic/ico/100/icons8-padlock-100.png \
    lib/kb4/pic/ico/100/icons8-save-100.png \
    lib/kb4/pic/ico/100/icons8-save-all-100.png \
    lib/kb4/pic/ico/100/icons8-save-as-100.png \
    lib/kb4/pic/ico/100/icons8-save-close-100.png \
    lib/kb4/pic/ico/100/icons8-sign-out-100.png \
    lib/kb4/pic/ico/100/icons8-terms-and-conditions-100.png \
    lib/kb4/pic/ico/100/icons8-toggle-off-100.png \
    lib/kb4/pic/ico/100/icons8-toggle-on-100.png \
    lib/kb4/pic/ico/100/icons8-upload-100.png \
    lib/kb4/pic/ico/100/icons8-window-cloud-100.png \
    lib/kb4/pic/ico/100/icons8-window-settings-100.png \
    lib/kb4/pic/ico/500/icons8-about-500.png \
    lib/kb4/pic/ico/500/icons8-add-500-2.png \
    lib/kb4/pic/ico/500/icons8-add-500-3.png \
    lib/kb4/pic/ico/500/icons8-add-500.png \
    lib/kb4/pic/ico/500/icons8-ask-question-500.png \
    lib/kb4/pic/ico/500/icons8-cancel-500.png \
    lib/kb4/pic/ico/500/icons8-checked-500.png \
    lib/kb4/pic/ico/500/icons8-checkmark-500.png \
    lib/kb4/pic/ico/500/icons8-document-500.png \
    lib/kb4/pic/ico/500/icons8-double-tick-500.png \
    lib/kb4/pic/ico/500/icons8-error-500.png \
    lib/kb4/pic/ico/500/icons8-eye-500-2.png \
    lib/kb4/pic/ico/500/icons8-eye-500.png \
    lib/kb4/pic/ico/500/icons8-folder-500.png \
    lib/kb4/pic/ico/500/icons8-invisible-500-2.png \
    lib/kb4/pic/ico/500/icons8-invisible-500.png \
    lib/kb4/pic/ico/500/icons8-lock-500.png \
    lib/kb4/pic/ico/500/icons8-login-500.png \
    lib/kb4/pic/ico/500/icons8-maintenance-500.png \
    lib/kb4/pic/ico/500/icons8-minus-500-2.png \
    lib/kb4/pic/ico/500/icons8-minus-500.png \
    lib/kb4/pic/ico/500/icons8-offline-500.png \
    lib/kb4/pic/ico/500/icons8-online-500.png \
    lib/kb4/pic/ico/500/icons8-opened-folder-500.png \
    lib/kb4/pic/ico/500/icons8-padlock-500.png \
    lib/kb4/pic/ico/500/icons8-save-500.png \
    lib/kb4/pic/ico/500/icons8-save-all-500.png \
    lib/kb4/pic/ico/500/icons8-save-as-500.png \
    lib/kb4/pic/ico/500/icons8-save-close-500.png \
    lib/kb4/pic/ico/500/icons8-sign-out-500.png \
    lib/kb4/pic/ico/500/icons8-terms-and-conditions-500.png \
    lib/kb4/pic/ico/500/icons8-toggle-off-500.png \
    lib/kb4/pic/ico/500/icons8-toggle-on-500.png \
    lib/kb4/pic/ico/500/icons8-upload-500.png \
    lib/kb4/pic/ico/500/icons8-window-cloud-500.png \
    lib/kb4/pic/ico/500/icons8-window-settings-500.png \
    lib/kb4/pic/ico/print.png \
    lib/kb4/pic/ico/screenshot.png \
    lib/kb4/pic/ui-gradientlineedit-gears.png \
    lib/kb4/pic/ui-realtimeqcp-cursor01.PNG \
    lib/kb4/pic/ui-realtimeqcp-cursor0102 — копия.PNG \
    lib/kb4/pic/ui-realtimeqcp-cursor0102.PNG \
    lib/kb4/pic/ui-realtimeqcp-mouse-area.PNG \
    lib/kb4/pic/ui-realtimeqcp-realtime.PNG \
    lib/kb4/pic/ui-realtimeqcp.PNG \
    lib/kb4/shared-variable/tcp/netvars/example/example.7z \
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
    lib/kb4/ui/plots/base/axisconfig.ui \
    lib/kb4/ui/plots/base/graphlegenditem.ui \
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
    lib/kb4/log/channelt.h \
    lib/kb4/log/excel/excel.h \
    lib/kb4/log/excel/excelfile.h \
    lib/kb4/log/excel/timelog/timelog.h \
    lib/kb4/log/log.h \
    lib/kb4/log/simple/simplelog.h \
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
    lib/kb4/ui/label/qlabelext.h \
    lib/kb4/ui/plots/base/abstractgraph.h \
    lib/kb4/ui/plots/base/abstractplot.h \
    lib/kb4/ui/plots/base/axisconfig.h \
    lib/kb4/ui/plots/base/colorsetter.h \
    lib/kb4/ui/plots/base/graphlegenditem.h \
    lib/kb4/ui/plots/radar/radargraph.h \
    lib/kb4/ui/plots/radar/radarplot.h \
    lib/kb4/ui/plots/radar/radartemperature4graph.h \
    lib/kb4/ui/plots/radar/radartemperature4plot.h \
    lib/kb4/ui/plots/realtime/realtimegraph.h \
    lib/kb4/ui/plots/realtime/realtimeplot.h \
    lib/kb4/ui/printscreener/printscreener.h \
    lib/kb4/ui/scientificnotationedit/scientificnotationedit.h \
    lib/kb4/ui/value/double/valuedouble.h \
    lib/kb4/worker/worker.h \
    lib/qcustomplot/qcustomplot.h \
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
    lib/kb4/log/excel/timelog/timelog.cpp \
    lib/kb4/log/log.cpp \
    lib/kb4/log/simple/simplelog.cpp \
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
    lib/kb4/ui/label/qlabelext.cpp \
    lib/kb4/ui/plots/base/abstractgraph.cpp \
    lib/kb4/ui/plots/base/abstractplot.cpp \
    lib/kb4/ui/plots/base/axisconfig.cpp \
    lib/kb4/ui/plots/base/colorsetter.cpp \
    lib/kb4/ui/plots/base/graphlegenditem.cpp \
    lib/kb4/ui/plots/radar/radargraph.cpp \
    lib/kb4/ui/plots/radar/radarplot.cpp \
    lib/kb4/ui/plots/radar/radartemperature4graph.cpp \
    lib/kb4/ui/plots/radar/radartemperature4plot.cpp \
    lib/kb4/ui/plots/realtime/realtimegraph.cpp \
    lib/kb4/ui/plots/realtime/realtimeplot.cpp \
    lib/kb4/ui/printscreener/printscreener.cpp \
    lib/kb4/ui/scientificnotationedit/scientificnotationedit.cpp \
    lib/kb4/ui/value/double/valuedouble.cpp \
    lib/kb4/worker/worker.cpp \
    lib/qcustomplot/qcustomplot.cpp \
    main.cpp \
    mainwindow.cpp
