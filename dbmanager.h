
#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include "wlapperimage.h"
class DBManager {
public:

    virtual void connectToDataBase() = 0;

    virtual QSqlDatabase getDB() = 0;

    virtual bool insertIntoImageTable(const WlapperImage& wlapperImage)=0;
    virtual QVector<WlapperImage> getAllImages() = 0;
    /*virtual bool inserIntoTable(const User& user) = 0;
    virtual bool updateAccountBalance(int accountId, double newBalance) =0;
    virtual bool updateAccountAmount(int accountId, double newAmount) = 0;
    virtual Payment getPaymentById(int paymentId)= 0;
    virtual Account getAccountById(int accountId) =0;
    virtual User getUserById(int userId) = 0;
    virtual int findUserIdByUsername(const QString &usernameToFind) = 0;
    virtual QVector<QString> getAllAccountNamesForCurrentUser(int currentUserId) = 0;
    virtual QVector<QString> getAllPaymentNamesForCurrentUser(int currentUserId) = 0;
    virtual Account getAccountByName(const QString &accountName) = 0;
    virtual Payment getPaymentByName(const QString &paymentName) = 0;
    virtual Payment* getLastPaymentForAccount(int currentAccountId) = 0;
    virtual Account* getLastAccountForUser(int currentUserId) =0;*/
};

#endif // DBMANAGER_H
