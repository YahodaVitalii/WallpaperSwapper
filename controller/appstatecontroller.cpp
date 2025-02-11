#include "appstatecontroller.h"

AppStateController::AppStateController(QObject* parent)
    : QObject(parent){}



//void AppStateController::updateStateFromMainWindow(const AppState& state, WallpaperImage image)
//{
//    stateChanged(state, image);
//}

void AppStateController::updateStateFromMainWindow(const AppState &state, BaseImageList *imageList)
{
    stateChanged(state, imageList);
}
