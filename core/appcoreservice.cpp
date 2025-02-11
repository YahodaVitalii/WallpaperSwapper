#include "appcoreservice.h"

AppCoreService::AppCoreService(QObject* parent, AppStateController* appStateController) : QObject(parent), appStateController(appStateController){}

void AppCoreService::performBackgroundTask() {

    QSettings settings(APP_NAME);
    settings.setValue("LastExecution", QDateTime::currentDateTime().toString());
    qDebug() << "Background task executed at:" << QDateTime::currentDateTime().toString();
}
