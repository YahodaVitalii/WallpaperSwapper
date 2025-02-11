#ifndef APPCORESERVICE_H
#define APPCORESERVICE_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <QDateTime>
#include "controller/appstatecontroller.h"
#include "constants/constants.h"

class AppCoreService : public QObject
{
    Q_OBJECT
public:
   explicit AppCoreService(QObject* parent = nullptr, AppStateController* appStateController = nullptr);
    void performBackgroundTask();
private:
    AppStateController* appStateController;
};
#endif // APPCORESERVICE_H
