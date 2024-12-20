#include "databasehandler.h"
#include <QSqlError>
#include <QDebug>

DatabaseHandler::DatabaseHandler(QObject *parent) : QObject(parent) {}

bool DatabaseHandler::connectToDatabase(const QString &host, const QString &dbname, const QString &user, const QString &password) {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("opengl");
    db.setUserName("root");
    db.setPassword("root1");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return false;
    }
    qDebug() << "Connected to database";
    return true;
}

QVariantList DatabaseHandler::fetchAllUsers() {
    QVariantList users;
    QSqlQuery query("SELECT id, name, email FROM users");
    while (query.next()) {
        QVariantMap user;
        user["id"] = query.value(0).toInt();
        user["name"] = query.value(1).toString();
        user["email"] = query.value(2).toString();
        users.append(user);
    }
    return users;
}

// Implémentation de la méthode addUser
bool DatabaseHandler::addUser(const QString &name, const QString &email) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (name, email) VALUES (?, ?)");
    query.addBindValue(name);
    query.addBindValue(email);
    return query.exec();
}

// Implémentation de la méthode updateUser
bool DatabaseHandler::updateUser(int id, const QString &name, const QString &email) {
    QSqlQuery query;
    query.prepare("UPDATE users SET name = ?, email = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(email);
    query.addBindValue(id);
    return query.exec();
}

// Implémentation de la méthode deleteUser
bool DatabaseHandler::deleteUser(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = ?");
    query.addBindValue(id);
    return query.exec();
}
