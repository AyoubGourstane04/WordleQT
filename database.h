#ifndef DATABASE_H
#define DATABASE_H

#include<QtSql/QSqlError>
#include<QtSql/QSqlQuery>
#include<QDebug>
#include<QtSql/QSqlDatabase>
#include<QVariantMap>

class Database
{
public:
    Database();
    static bool initializeDatabase();
    static bool createUser(const QString &firstName, const QString &lastName, const QString &birthdate,
                           const QString &username, const QString &password);
    static bool authenticateUser(const QString &username, const QString &password);

    static QVariantMap getUserByUsername(const QString &username);

    static void AlterScore(const QString &username);





};

#endif // DATABASE_H
