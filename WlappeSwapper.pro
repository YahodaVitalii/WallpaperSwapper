QT += core gui widgets

QT += sql
LIBS += -lUser32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogwindowlistofimage.cpp \
    imagemanager.cpp \
    interfaceaddition.cpp \
    main.cpp \
    mainwindow.cpp \
    sqlitedbmanager.cpp \
    standarttab.cpp \
    style.cpp \
    timetab.cpp \
    timetabrrandomlistwidget.cpp \
    wlapperimage.cpp

HEADERS += \
    dbmanager.h \
    dialogwindowlistofimage.h \
    imagemanager.h \
    interfaceaddition.h \
    mainwindow.h \
    sqlitedbmanager.h \
    standarttab.h \
    style.h \
    timetab.h \
    timetabrrandomlistwidget.h \
    wlapperimage.h

FORMS += \
    dialogwindowlistofimage.ui \
    mainwindow.ui \
    standarttab.ui \
    timetab.ui \
    timetabrrandomlistwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
