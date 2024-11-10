QT += core gui widgets

QT += sql
LIBS += -lUser32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baseimagelist.cpp \
    baselistwidget.cpp \
    customlabel.cpp \
    dayimagelist.cpp \
    daylisttablemanager.cpp \
    daylistwidget.cpp \
    dayofweek.cpp \
    dayviewimageslider.cpp \
    dbtablemanager.cpp \
    dbtablescreator.cpp \
    dialogwindowcontroller.cpp \
    dialogwindowlistofimage.cpp \
    emodjitablemanager.cpp \
    imagelist.cpp \
    imageloader.cpp \
    imagetablemanager.cpp \
    interfaceaddition.cpp \
    listtablemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    moodlisttablemeneger.cpp \
    moodtab.cpp \
    randomimagelist.cpp \
    randomlisttablemanager.cpp \
    randomlistwidget.cpp \
    randomviewimageslider.cpp \
    scrollareamanager.cpp \
    sqlitedbmanager.cpp \
    sqltableimagelist.cpp \
    standarttab.cpp \
    standarttabimageslider.cpp \
    style.cpp \
    tabwidgetfactory.cpp \
    timetab.cpp \
    timetabwidgets.cpp \
    uielementeventhandler.cpp \
    uielementfactory.cpp \
    uiimageslider.cpp \
    wallpaperimage.cpp \
    wallpapersetter.cpp \
    weekimagelist.cpp \
    weeklisttablemanager.cpp \
    weeklistwidget.cpp \
    weekviewimageslider.cpp \
    wsexception.cpp

HEADERS += \
    baseimagelist.h \
    baselistwidget.h \
    customlabel.h \
    dayimagelist.h \
    daylisttablemanager.h \
    daylistwidget.h \
    dayofweek.h \
    dayviewimageslider.h \
    dbmanager.h \
    dbtablemanager.h \
    dbtablescreator.h \
    dialogwindowcontroller.h \
    dialogwindowlistofimage.h \
    emodjitablemanager.h \
    imagelist.h \
    imageloader.h \
    imagetablemanager.h \
    interfaceaddition.h \
    listtablemanager.h \
    mainwindow.h \
    moodlisttablemeneger.h \
    moodtab.h \
    randomimagelist.h \
    randomlisttablemanager.h \
    randomlistwidget.h \
    randomviewimageslider.h \
    scrollareamanager.h \
    sqlitedbmanager.h \
    sqltableimagelist.h \
    standarttab.h \
    standarttabimageslider.h \
    style.h \
    tabwidgetfactory.h \
    timetab.h \
    timetabwidgets.h \
    uielementeventhandler.h \
    uielementfactory.h \
    uiimageslider.h \
    wallpaperimage.h \
    wallpapersetter.h \
    weekimagelist.h \
    weeklisttablemanager.h \
    weeklistwidget.h \
    weekviewimageslider.h \
    widgetgeometry.h \
    wsexception.h

FORMS += \
    daylistwidget.ui \
    dialogwindowlistofimage.ui \
    mainwindow.ui \
    moodtab.ui \
    randomlistwidget.ui \
    standarttab.ui \
    timetab.ui \
    weeklistwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
