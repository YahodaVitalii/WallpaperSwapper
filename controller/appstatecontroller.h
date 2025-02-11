#ifndef APPSTATECONTROLLER_H
#define APPSTATECONTROLLER_H

#include <QObject>
#include <QString>
#include"enums/appState.h"
#include "models/wallpaperimage.h"
#include "models/baseimagelist.h"

class AppStateController : public QObject
{
    Q_OBJECT

public:
    explicit AppStateController(QObject* parent = nullptr);


signals:
    void stateChanged(const AppState& state, WallpaperImage* image);
    void stateChanged(const AppState& state, BaseImageList* imageList);

public slots:
    //void updateStateFromMainWindow(const AppState& state, WallpaperImage* image);
    void updateStateFromMainWindow(const AppState& state, BaseImageList* imageList);
};

#endif // APPSTATECONTROLLER_H
