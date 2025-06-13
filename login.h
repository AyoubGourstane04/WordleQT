#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include <QSpacerItem>
#include <QMessageBox>
#include<QShowEvent>






class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

protected:
    void showEvent(QShowEvent *event) override;



private:
    QLineEdit *UserNameEdit;
    QLineEdit *PasswordEdit;
    QPushButton *loginBtn;
    QPushButton *signupBtn;



public slots:
    void signupRedirect();
    void mainRedirect();
    void login();


};




#endif // LOGIN_H
