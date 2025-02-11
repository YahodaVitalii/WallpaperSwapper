QT += core gui widgets

QT += sql
LIBS += -lUser32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DB/TablesManagers/daylisttablemanager.cpp \
    DB/TablesManagers/dbtablemanager.cpp \
    DB/TablesManagers/emodjitablemanager.cpp \
    DB/TablesManagers/imagetablemanager.cpp \
    DB/TablesManagers/listtablemanager.cpp \
    DB/TablesManagers/moodlisttablemeneger.cpp \
    DB/TablesManagers/randomlisttablemanager.cpp \
    DB/TablesManagers/weeklisttablemanager.cpp \
    DB/dbtablescreator.cpp \
    DB/sqlitedbmanager.cpp \
    GUI/CustomWidgets/customlabel.cpp \
    GUI/CustomWidgets/interfaceaddition.cpp \
    GUI/CustomWidgets/sliders/dayviewimageslider.cpp \
    GUI/CustomWidgets/sliders/randomviewimageslider.cpp \
    GUI/CustomWidgets/sliders/standarttabimageslider.cpp \
    GUI/CustomWidgets/sliders/uiimageslider.cpp \
    GUI/CustomWidgets/sliders/weekviewimageslider.cpp \
    GUI/CustomWidgets/uielementeventhandler.cpp \
    GUI/CustomWidgets/uielementfactory.cpp \
    GUI/service/dialogwindowcontroller.cpp \
    GUI/service/scrollareamanager.cpp \
    GUI/service/tabwidgetfactory.cpp \
    GUI/style/style.cpp \
    controller/appstatecontroller.cpp \
    core/appcoreservice.cpp \
    core/imageloader.cpp \
    core/states/appstate.cpp \
    core/states/daystate.cpp \
    core/states/moodstate.cpp \
    core/states/randomstate.cpp \
    core/states/standartstate.cpp \
    core/states/timestate.cpp \
    core/states/weekstate.cpp \
    core/wallpapersetter.cpp \
    enums/dayofweek.cpp \
    exception/wsexception.cpp \
    main.cpp \
    models/baseimagelist.cpp \
    models/dayimagelist.cpp \
    models/imagelist.cpp \
    models/randomimagelist.cpp \
    models/sqltableimagelist.cpp \
    models/wallpaperimage.cpp \
    models/weekimagelist.cpp \
    widgets/baselistwidget.cpp \
    widgets/daylistwidget.cpp \
    widgets/mainwindow.cpp \
    widgets/moodtab.cpp \
    widgets/randomlistwidget.cpp \
    widgets/settingtab.cpp \
    widgets/standarttab.cpp \
    widgets/timetab.cpp \
    widgets/timetabchildrenwidget.cpp \
    widgets/weeklistwidget.cpp \
    window/dialog/basedialogwindow.cpp \
    window/dialog/windowchoosemood.cpp \
    window/dialog/windowlistofimage.cpp

HEADERS += \
    DB/TablesManagers/daylisttablemanager.h \
    DB/TablesManagers/dbtablemanager.h \
    DB/TablesManagers/emodjitablemanager.h \
    DB/TablesManagers/imagetablemanager.h \
    DB/TablesManagers/listtablemanager.h \
    DB/TablesManagers/moodlisttablemeneger.h \
    DB/TablesManagers/randomlisttablemanager.h \
    DB/TablesManagers/weeklisttablemanager.h \
    DB/dbmanager.h \
    DB/dbtablescreator.h \
    DB/sqlitedbmanager.h \
    GUI/CustomWidgets/customlabel.h \
    GUI/CustomWidgets/interfaceaddition.h \
    GUI/CustomWidgets/sliders/dayviewimageslider.h \
    GUI/CustomWidgets/sliders/randomviewimageslider.h \
    GUI/CustomWidgets/sliders/standarttabimageslider.h \
    GUI/CustomWidgets/sliders/uiimageslider.h \
    GUI/CustomWidgets/sliders/weekviewimageslider.h \
    GUI/CustomWidgets/uielementeventhandler.h \
    GUI/CustomWidgets/uielementfactory.h \
    GUI/service/dialogwindowcontroller.h \
    GUI/service/scrollareamanager.h \
    GUI/service/tabwidgetfactory.h \
    GUI/style/style.h \
    GUI/style/widgetgeometry.h \
    constants/constants.h \
    controller/appstatecontroller.h \
    core/appcoreservice.h \
    core/imageloader.h \
    core/states/appstate.h \
    core/states/daystate.h \
    core/states/moodstate.h \
    core/states/randomstate.h \
    core/states/standartstate.h \
    core/states/timestate.h \
    core/states/weekstate.h \
    core/wallpapersetter.h \
    enums/appState.h \
    enums/dayofweek.h \
    enums/dialogwindows.h \
    exception/wsexception.h \
    models/baseimagelist.h \
    models/dayimagelist.h \
    models/imagelist.h \
    models/randomimagelist.h \
    models/sqltableimagelist.h \
    models/wallpaperimage.h \
    models/weekimagelist.h \
    struct/timerangeimage.h \
    widgets/baselistwidget.h \
    widgets/daylistwidget.h \
    widgets/mainwindow.h \
    widgets/moodtab.h \
    widgets/randomlistwidget.h \
    widgets/settingtab.h \
    widgets/standarttab.h \
    widgets/timetab.h \
    widgets/timetabchildrenwidget.h \
    widgets/weeklistwidget.h \
    window/dialog/basedialogwindow.h \
    window/dialog/windowchoosemood.h \
    window/dialog/windowlistofimage.h

FORMS += \
    daylistwidget.ui \
    mainwindow.ui \
    moodtab.ui \
    randomlistwidget.ui \
    settingtab.ui \
    standarttab.ui \
    timetab.ui \
    weeklistwidget.ui \
    window/dialog/windowchoosemood.ui \
    window/dialog/windowlistofimage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
