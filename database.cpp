#include "database.h"

Database::Database() {}




bool Database::initializeDatabase()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("wordle_users.db");

    if(!db.open()){
        qDebug()<<"Error : Failed to connect to database : "<<db.lastError().text();
        return false;
    }
    QSqlQuery query;

    query.prepare("CREATE TABLE IF NOT EXISTS users("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "firstName TEXT NOT NULL,"
                  "lastName TEXT NOT NULL,"
                  "birthdate TEXT NOT NULL,"
                  "userName TEXT UNIQUE NOT NULL,"
                  "password TEXT NOT NULL,"
                  " score int DEFAULT '0')");
    if(!query.exec()){
        qDebug()<<"Error : Failed to create the table : "<<db.lastError().text();
        return false;
    }
    return true;
}


bool Database::createUser(const QString &firstName, const QString &lastName, const QString &birthdate, const QString &username, const QString &password)
{
    QSqlQuery query;

    query.prepare("INSERT INTO users (firstName,lastName,birthdate,userName,password) VALUES (:firstName,:lastName,:birthdate,:userName,:password);");
    query.bindValue(":firstName",firstName);
    query.bindValue(":lastName",lastName);
    query.bindValue(":birthdate",birthdate);
    query.bindValue(":userName",username);
    query.bindValue(":password",password);

    return query.exec();
}


bool Database::authenticateUser(const QString &username, const QString &password)
{
    QSqlQuery query;

    query.prepare("SELECT password FROM users WHERE userName=:userName;");
    query.bindValue(":userName",username);

    if(!query.exec()){
        qDebug()<<"Login Error : "<<query.lastError().text();
        return false;
    }

    if(query.next()){
        QString userPassword=query.value(0).toString();
        return userPassword==password;
    }

    return false;
}

QVariantMap Database::getUserByUsername(const QString &username)
{
    QVariantMap user;

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE userName = :userName");
    query.bindValue(":userName", username);

    if (!query.exec()) {
        qDebug() << "Error fetching user:" << query.lastError().text();
        return user;
    }

    if (query.next()) {
        user["id"] = query.value("id");
        user["firstName"] = query.value("firstName");
        user["lastName"] = query.value("lastName");
        user["birthdate"] = query.value("birthdate");
        user["userName"] = query.value("userName");
        user["password"] = query.value("password");
        user["score"] = query.value("score");
    }

    return user;
}


void Database::AlterScore(const QString &username)
{
    Database::getUserByUsername(username);

    QVariantMap User = Database::getUserByUsername(username);
    int score = User["score"].toInt();

    qDebug() << "[DEBUG] AlterScore called for user:" << username << "with score:" << score;


    QSqlQuery query;

    int newScore = score + 1;

    query.prepare("UPDATE users SET score = :score WHERE userName = :userName;");
    query.bindValue(":score", newScore);
    query.bindValue(":userName", username);

    if (!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "No rows updated. Possibly incorrect username.";
        return;
    }

    qDebug() << "[DEBUG] Score updated successfully.";
}

