QT += core gui widgets

QT += sql
LIBS += -lUser32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baselistwidget.cpp \
    dayimagelist.cpp \
    dayviewimageslider.cpp \
    dbdaylisttablemanager.cpp \
    dbimagetablemanager.cpp \
    dbrandomlisttablemanager.cpp \
    dbtablescreator.cpp \
    dbweeklisttablemanager.cpp \
    dialogwindowcontroller.cpp \
    dialogwindowlistofimage.cpp \
    imagelist.cpp \
    imageloader.cpp \
    interfaceaddition.cpp \
    main.cpp \
    mainwindow.cpp \
    randomimagelist.cpp \
    randomviewimageslider.cpp \
    scrollareamanager.cpp \
    sqlitedbmanager.cpp \
    sqltableimagelist.cpp \
    standarttab.cpp \
    standarttabimageslider.cpp \
    style.cpp \
    tabinterfacebuilder.cpp \
    timetab.cpp \
    timetabdaylistwidget.cpp \
    timetabrandomlistwidget.cpp \
    timetabweeklistwidget.cpp \
    uielementeventhandler.cpp \
    uielementfactory.cpp \
    uiimageslider.cpp \
    wallpaperimage.cpp \
    wallpapersetter.cpp \
    weekimagelist.cpp \
    weekviewimageslider.cpp \
    wsexeptions.cpp

HEADERS += \
    baselistwidget.h \
    dayimagelist.h \
    dayviewimageslider.h \
    dbdaylisttablemanager.h \
    dbimagetablemanager.h \
    dbmanager.h \
    dbrandomlisttablemanager.h \
    dbtablescreator.h \
    dbweeklisttablemanager.h \
    dialogwindowcontroller.h \
    dialogwindowlistofimage.h \
    imagelist.h \
    imageloader.h \
    interfaceaddition.h \
    mainwindow.h \
    randomimagelist.h \
    randomviewimageslider.h \
    scrollareamanager.h \
    sqlitedbmanager.h \
    sqltableimagelist.h \
    standarttab.h \
    standarttabimageslider.h \
    style.h \
    tabinterfacebuilder.h \
    timetab.h \
    timetabdaylistwidget.h \
    timetabrandomlistwidget.h \
    timetabweeklistwidget.h \
    uielementeventhandler.h \
    uielementfactory.h \
    uiimageslider.h \
    wallpaperimage.h \
    wallpapersetter.h \
    weekimagelist.h \
    weekviewimageslider.h \
    widgetgeometry.h \
    wsexeptions.h

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
