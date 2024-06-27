QT += core gui widgets serialport charts 

greaterThan(QT_MAJOR_VERSION, 4):
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chartmanager.cpp \
    console.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    serialmanager.cpp \
    toolbarmanager.cpp \

HEADERS += \
    chartmanager.h \
    console.h \
    common.h \
    mainwindow.h \
    settingsdialog.h \
    serialmanager.h \
    toolbarmanager.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += styles/*.qss \
             icons/*.png

# Copy the QSS file and PNG files to the build directory after building the project
QMAKE_POST_LINK += $$quote(cp $$PWD/styles/*.qss $$OUT_PWD/)
QMAKE_POST_LINK += $$quote(cp $$PWD/icons/*.png $$OUT_PWD/)
