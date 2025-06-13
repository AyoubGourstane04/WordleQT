#include "login.h"
#include "signup.h"
#include "widget.h"
#include "database.h"
#include <QCryptographicHash>




Login::Login(QWidget *parent)
{
    setWindowTitle("Login");
    setWindowIcon(QIcon(":/res/w-solid.svg"));
    resize(450, 550);  // Slightly larger for better spacing
    this->setStyleSheet(
        "background-color: #121212;"
        "color: #ffffff;"
        );

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(50, 50, 50, 50);
    mainLayout->setSpacing(30);

    // Header with back button and title
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(20);

    QPushButton *backButton = new QPushButton();
    backButton->setIcon(QIcon(":/res/circle-left-regular.svg"));
    backButton->setIconSize(QSize(24, 24));
    backButton->setFixedSize(45, 45);
    backButton->setStyleSheet(
        "QPushButton {"
        "background: transparent;"
        "border: 2px solid #4a90e2;"
        "border-radius: 22px;"
        "}"
        "QPushButton:hover {"
        "background-color: rgba(74, 144, 226, 0.15);"
        "}"
        "QPushButton:pressed {"
        "background-color: rgba(74, 144, 226, 0.25);"
        "}"
        );
    backButton->setCursor(Qt::PointingHandCursor);
    connect(backButton, &QPushButton::clicked, this, &Login::mainRedirect);

    QLabel *titleLabel = new QLabel("Login");
    titleLabel->setFont(QFont("Futura", 32, QFont::Bold));
    titleLabel->setStyleSheet(
        "color: white;"
        "letter-spacing: 1px;"
        );

    headerLayout->addWidget(backButton, 0, Qt::AlignLeft);
    headerLayout->addStretch();
    headerLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    headerLayout->addStretch();
    mainLayout->addLayout(headerLayout);

    // Subtitle
    QLabel *subtitleLabel = new QLabel("Welcome back! Please enter your details");
    subtitleLabel->setFont(QFont("Futura", 14));
    subtitleLabel->setStyleSheet(
        "color: #bbbbbb;"
        "margin-bottom: 10px;"
        );
    subtitleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(subtitleLabel);

    // Form layout
    QVBoxLayout *formLayout = new QVBoxLayout();
    formLayout->setSpacing(20);
    formLayout->setContentsMargins(0, 20, 0, 20);

    // Username field
    QLabel *usernameLabel = new QLabel("Username or Email");
    usernameLabel->setFont(QFont("Futura", 12, QFont::Medium));
    usernameLabel->setStyleSheet(
        "color: #dddddd;"
        "margin-bottom: 5px;"
        );

    UserNameEdit = new QLineEdit();
    UserNameEdit->setPlaceholderText("Enter your username or email");
    UserNameEdit->setFont(QFont("Futura", 14));
    UserNameEdit->setStyleSheet(
        "QLineEdit {"
        "padding: 12px 15px;"
        "border: 2px solid #3a3a3a;"
        "border-radius: 8px;"
        "background-color: #1e1e1e;"
        "color: white;"
        "selection-background-color: #4a90e2;"
        "}"
        "QLineEdit:focus {"
        "border: 2px solid #4a90e2;"
        "outline: none;"
        "}"
        );
    UserNameEdit->setFocus();

    // Password field
    QLabel *passwordLabel = new QLabel("Password");
    passwordLabel->setFont(QFont("Futura", 12, QFont::Medium));
    passwordLabel->setStyleSheet(
        "color: #dddddd;"
        "margin-bottom: 5px;"
        );

    PasswordEdit = new QLineEdit();
    PasswordEdit->setPlaceholderText("Enter your password");
    PasswordEdit->setFont(QFont("Futura", 14));
    PasswordEdit->setEchoMode(QLineEdit::Password);
    PasswordEdit->setStyleSheet(
        "QLineEdit {"
        "padding: 12px 15px;"
        "border: 2px solid #3a3a3a;"
        "border-radius: 8px;"
        "background-color: #1e1e1e;"
        "color: white;"
        "selection-background-color: #4a90e2;"
        "}"
        "QLineEdit:focus {"
        "border: 2px solid #4a90e2;"
        "outline: none;"
        "}"
        );

    // Connect return pressed events
    connect(UserNameEdit, &QLineEdit::returnPressed, this, [this]() { loginBtn->click(); });
    connect(PasswordEdit, &QLineEdit::returnPressed, this, [this]() { loginBtn->click(); });

    // Add fields to form
    formLayout->addWidget(usernameLabel);
    formLayout->addWidget(UserNameEdit);
    formLayout->addSpacing(10);
    formLayout->addWidget(passwordLabel);
    formLayout->addWidget(PasswordEdit);

    mainLayout->addLayout(formLayout);

    // Login button
    loginBtn = new QPushButton("LOGIN");
    loginBtn->setFont(QFont("Futura", 16, QFont::Bold));
    loginBtn->setStyleSheet(
        "QPushButton {"
        "background-color: #4a90e2;"
        "color: white;"
        "border: none;"
        "border-radius: 8px;"
        "padding: 14px;"
        "min-width: 120px;"
        "letter-spacing: 1px;"
        "}"
        "QPushButton:hover {"
        "background-color: #3a80d2;"
        "}"
        "QPushButton:pressed {"
        "background-color: #2a70c2;"
        "}"
        );
    loginBtn->setCursor(Qt::PointingHandCursor);
    loginBtn->setDefault(true);
    connect(loginBtn, &QPushButton::clicked, this, &Login::login);

    mainLayout->addWidget(loginBtn);

    // Signup prompt
    QHBoxLayout *signupLayout = new QHBoxLayout();
    signupLayout->setContentsMargins(0, 20, 0, 0);
    signupLayout->setSpacing(5);

    QLabel *signupPrompt = new QLabel("Don't have an account?");
    signupPrompt->setFont(QFont("Futura", 12));
    signupPrompt->setStyleSheet("color: #bbbbbb;");

    signupBtn = new QPushButton("Sign up");
    signupBtn->setFont(QFont("Futura", 12, QFont::Medium));
    signupBtn->setStyleSheet(
        "QPushButton {"
        "color: #4a90e2;"
        "background: transparent;"
        "border: none;"
        "font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "color: #3a80d2;"
        "text-decoration: underline;"
        "}"
        );
    signupBtn->setCursor(Qt::PointingHandCursor);
    connect(signupBtn, &QPushButton::clicked, this, &Login::signupRedirect);

    signupLayout->addStretch();
    signupLayout->addWidget(signupPrompt);
    signupLayout->addWidget(signupBtn);
    signupLayout->addStretch();

    mainLayout->addLayout(signupLayout);
    mainLayout->addStretch();
}


void Login::signupRedirect()
{
    this->hide();
    Signup *signup=new Signup();
    signup->show();
}


void Login::mainRedirect()
{
    this->hide();
    Widget *main=new Widget();
    main->show();
}


void Login::login()
{
    QString userName = UserNameEdit->text().trimmed();
    QString password = PasswordEdit->text();

    if(userName.isEmpty() || password.isEmpty()){
        QMessageBox::warning(this,"Login Failed","Please enter both username and password");
        return;
    }

    QString hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    if(Database::authenticateUser(userName,hashedPassword)){
        //QMessageBox::information(this,"Login success","Login successful!");
            this->hide();
            Widget *main=new Widget(userName);
            main->show();
    }else{
         QMessageBox::critical(this, "Error", "Invalid username or password.");
    }
}



void Login::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    UserNameEdit->setFocus();
}









Login::~Login()
{

}



