QT += core gui widgets

QT += sql
LIBS += -lUser32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dayimagelist.cpp \
    dialogwindowlistofimage.cpp \
    imagemanager.cpp \
    interfaceaddition.cpp \
    main.cpp \
    mainwindow.cpp \
    randomimagelist.cpp \
    sqlitedbmanager.cpp \
    standarttab.cpp \
    style.cpp \
    timetab.cpp \
    timetabdaylistwidget.cpp \
    timetabrandomlistwidget.cpp \
    timetabweeklistwidget.cpp \
    weekimagelist.cpp \
    wlapperimage.cpp

HEADERS += \
    dayimagelist.h \
    dbmanager.h \
    dialogwindowlistofimage.h \
    imagemanager.h \
    interfaceaddition.h \
    mainwindow.h \
    randomimagelist.h \
    sqlitedbmanager.h \
    standarttab.h \
    style.h \
    timetab.h \
    timetabdaylistwidget.h \
    timetabrandomlistwidget.h \
    timetabweeklistwidget.h \
    weekimagelist.h \
    wlapperimage.h

FORMS += \
    dialogwindowlistofimage.ui \
    mainwindow.ui \
    standarttab.ui \
    timetab.ui \
    timetabdaylistwidget.ui \
    timetabrandomlistwidget.ui \
    timetabweeklistwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
