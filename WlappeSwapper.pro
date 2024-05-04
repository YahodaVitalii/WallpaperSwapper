QT += core gui widgets

QT += sql
LIBS += -lUser32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogcreatenewiteminstandarttab.cpp \
    dialogwindowlistofimage.cpp \
    imagemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    randomlistimageseditadd.cpp \
    sqlitedbmanager.cpp \
    standarttab.cpp \
    style.cpp \
    timetab.cpp \
    wlapperimage.cpp

HEADERS += \
    dbmanager.h \
    dialogcreatenewiteminstandarttab.h \
    dialogwindowlistofimage.h \
    imagemanager.h \
    mainwindow.h \
    randomlistimageseditadd.h \
    sqlitedbmanager.h \
    standarttab.h \
    style.h \
    timetab.h \
    wlapperimage.h

FORMS += \
    dialogcreatenewiteminstandarttab.ui \
    dialogwindowlistofimage.ui \
    mainwindow.ui \
    randomlistimageseditadd.ui \
    standarttab.ui \
    timetab.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
