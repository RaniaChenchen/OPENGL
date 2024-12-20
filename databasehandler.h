
#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QSqlDatabase>
#include <QSqlQuery>

class DatabaseHandler : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseHandler(QObject *parent = nullptr);

    bool connectToDatabase(const QString &host, const QString &dbname, const QString &user, const QString &password);
    QVariantList fetchAllUsers();

    // Déclaration des fonctions addUser, updateUser, deleteUser
    bool addUser(const QString &name, const QString &email);
    bool updateUser(int id, const QString &name, const QString &email);
    bool deleteUser(int id);

private:
    QSqlDatabase db;
};

#endif // DATABASEHANDLER_H

