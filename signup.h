#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include<QMessageBox>
#include<QObject>
#include<QEvent>
#include<QKeyEvent>


class Signup : public QWidget
{
    Q_OBJECT

public:
    Signup(QWidget *parent = nullptr);
    ~Signup();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;


private:
    QVBoxLayout *mainVbox;
    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QDateEdit *birthDateEdit;
    QLineEdit *userNameEdit;
    QLineEdit *passwordEdit;
    QPushButton *signupBtn;
    QPushButton *loginBtn;


public slots:
    void loginRedirect();
    void signup();

};

#endif // SIGNUP_H
