/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLineEdit *userInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(500, 400);
        Login->setStyleSheet(QString::fromUtf8("\n"
"       background-color: #121212;\n"
"       color: #ffffff;\n"
"       font-family: Futura;\n"
"   "));
        verticalLayout = new QVBoxLayout(Login);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setAlignment(Qt::AlignCenter);
        titleLabel = new QLabel(Login);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Futura")});
        font.setPointSize(28);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet(QString::fromUtf8("color: #eee; font-weight: bold;"));

        verticalLayout->addWidget(titleLabel);

        userInput = new QLineEdit(Login);
        userInput->setObjectName("userInput");
        userInput->setStyleSheet(QString::fromUtf8("\n"
"        background-color: #1e1e1e;\n"
"        border: 1px solid #333;\n"
"        border-radius: 8px;\n"
"        padding: 10px;\n"
"        color: #eee;\n"
"        font-size: 16px;\n"
"      "));

        verticalLayout->addWidget(userInput);

        passwordInput = new QLineEdit(Login);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setEchoMode(QLineEdit::Password);
        passwordInput->setStyleSheet(QString::fromUtf8("\n"
"        background-color: #1e1e1e;\n"
"        border: 1px solid #333;\n"
"        border-radius: 8px;\n"
"        padding: 10px;\n"
"        color: #eee;\n"
"        font-size: 16px;\n"
"      "));

        verticalLayout->addWidget(passwordInput);

        loginButton = new QPushButton(Login);
        loginButton->setObjectName("loginButton");
        loginButton->setStyleSheet(QString::fromUtf8("\n"
"        QPushButton {\n"
"            background-color: #4CAF50;\n"
"            border-radius: 8px;\n"
"            padding: 10px;\n"
"            font-weight: bold;\n"
"            font-size: 18px;\n"
"            color: white;\n"
"        }\n"
"        QPushButton:hover {\n"
"            background-color: #45a049;\n"
"        }\n"
"      "));

        verticalLayout->addWidget(loginButton);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login", nullptr));
        titleLabel->setText(QCoreApplication::translate("Login", "Welcome Back!", nullptr));
        userInput->setPlaceholderText(QCoreApplication::translate("Login", "Username or Email", nullptr));
        passwordInput->setPlaceholderText(QCoreApplication::translate("Login", "Password", nullptr));
        loginButton->setText(QCoreApplication::translate("Login", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
