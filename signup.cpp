#include "signup.h"
#include "login.h"
#include<QCryptographicHash>
#include "database.h"


Signup::Signup(QWidget *parent)
{
    setWindowTitle("Sign Up");
    setWindowIcon(QIcon(":/res/w-solid.svg"));
    resize(300,500);
    this->setStyleSheet(
        "background-color: #121212;"
        "color: #ffffff;"
        );

    // Interface :

    mainVbox=new QVBoxLayout(this);
    mainVbox->setContentsMargins(40,40,40,40);
    mainVbox->setSpacing(10);

    QLabel *title=new QLabel();
    title->setText("Create an account ");
    title->setFont(QFont("Futura",28));
    title->setStyleSheet("color: white; margin-bottom: 10px; font-weight: bold;");

    mainVbox->addWidget(title,0,Qt::AlignHCenter);

    QVBoxLayout *formVbox=new QVBoxLayout();
    formVbox->setSpacing(10);


    // FirstName:

    QLabel *firstNameLabel = new QLabel("First Name");
    firstNameLabel->setFont(QFont("Futura", 14));
    firstNameLabel->setStyleSheet("color: white; margin-bottom: 5px; font-weight: bold;");

    firstNameEdit = new QLineEdit();
    firstNameEdit->setPlaceholderText("Enter your first name");
    firstNameEdit->setStyleSheet(
        "QLineEdit {"
        "padding: 10px;"
        "border: 2px solid #3a3a3a;"
        "border-radius: 8px;"
        "background-color: #1e1e1e;"
        "color: white;"
        "min-height: 25px;"
        "}"
        "QLineEdit:focus {"
        "border: 2px solid #4a90e2;"
        "outline: none;"
        "}"
        );
    connect(firstNameEdit, &QLineEdit::returnPressed, this, [this]() {
        signupBtn->click();
    });

    formVbox->addWidget(firstNameLabel);
    formVbox->addWidget(firstNameEdit);

    // LastName:

    QLabel *lastNameLabel = new QLabel("Last Name");
    lastNameLabel->setFont(QFont("Futura", 14));
    lastNameLabel->setStyleSheet("color: white; margin-bottom: 5px; font-weight: bold;");

    lastNameEdit = new QLineEdit();
    lastNameEdit->setPlaceholderText("Enter your last name");
    lastNameEdit->setStyleSheet(firstNameEdit->styleSheet());

    connect(lastNameEdit, &QLineEdit::returnPressed, this, [this]() {
        signupBtn->click();
    });

    formVbox->addWidget(lastNameLabel);
    formVbox->addWidget(lastNameEdit);

    // Birthdate:

    QLabel *birthDateLabel = new QLabel("Birth Date");
    birthDateLabel->setFont(QFont("Futura", 14));
    birthDateLabel->setStyleSheet("color: white; margin-bottom: 5px; font-weight: bold;");

    birthDateEdit = new QDateEdit();
    birthDateEdit->setCalendarPopup(true);
    birthDateEdit->setDate(QDate::currentDate());
    birthDateEdit->setMaximumDate(QDate::currentDate());
    birthDateEdit->setStyleSheet(
        "QDateEdit {"
        "padding: 8px;"
        "border: 2px solid #3a3a3a;"
        "border-radius: 8px;"
        "background-color: #1e1e1e;"
        "color: white;"
        "min-height: 25px;"
        "}"
        "QDateEdit:focus {"
        "border: 2px solid #4a90e2;"
        "outline: none;"
        "}"
        "QCalendarWidget QWidget {"
        "background-color: #1e1e1e;"
        "color: white;"
        "}"
        );
    birthDateEdit->installEventFilter(this);

    formVbox->addWidget(birthDateLabel);
    formVbox->addWidget(birthDateEdit);


    // Username:

    QLabel *userNameLabel = new QLabel("Username or Email");
    userNameLabel->setFont(QFont("Futura", 14));
    userNameLabel->setStyleSheet("color: white; margin-bottom: 5px; font-weight: bold;");

    userNameEdit = new QLineEdit();
    userNameEdit->setPlaceholderText("Enter your username or email");
    userNameEdit->setStyleSheet(firstNameEdit->styleSheet());

    connect(userNameEdit, &QLineEdit::returnPressed, this, [this]() {
        signupBtn->click();
    });

    formVbox->addWidget(userNameLabel);
    formVbox->addWidget(userNameEdit);

    // Password:

    QLabel *passwordLabel = new QLabel("Password");
    passwordLabel->setFont(QFont("Futura", 14));
    passwordLabel->setStyleSheet("color: white; margin-bottom: 5px; font-weight: bold;");

    passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("Enter your password");
    passwordEdit->setStyleSheet(firstNameEdit->styleSheet());
    passwordEdit->setEchoMode(QLineEdit::Password);

    connect(passwordEdit, &QLineEdit::returnPressed, this, [this]() {
        signupBtn->click();
    });

    formVbox->addWidget(passwordLabel);
    formVbox->addWidget(passwordEdit);

    mainVbox->addLayout(formVbox);


    // Signup button:
    signupBtn = new QPushButton("Sign Up");
    signupBtn->setFont(QFont("Futura", 16));
    signupBtn->setStyleSheet(
        "QPushButton {"
        "background-color: #4a90e2;"
        "color: white;"
        "border: none;"
        "padding: 12px;"
        "margin-top: 10px;"
        "border-radius: 4px;"
        "font-weight: bold;"
        "min-height: 30px;"
        "}"
        "QPushButton:hover {"
        "background-color: #3a80d2;"
        "}"
        "QPushButton:pressed {"
        "background-color: #2a70c2;"
        "}"
        );
    signupBtn->setCursor(Qt::PointingHandCursor);
    signupBtn->setDefault(true);






    connect(signupBtn,SIGNAL(clicked(bool)),this,SLOT(signup()));
    mainVbox->addWidget(signupBtn);

    // Login stuff:
    QHBoxLayout *loginLayout = new QHBoxLayout();
    loginLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QLabel *loginLabel = new QLabel("Already have an account?");
    loginLabel->setFont(QFont("Futura", 12));

    loginBtn = new QPushButton("Login");
    loginBtn->setFont(QFont("Futura", 12));
    loginBtn->setStyleSheet(
        "QPushButton {"
        "color: #4a90e2;"
        "background: transparent;"
        "border: none;"
        "text-decoration: underline;"
        "font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "background-color: #1e1e1e;"
        "}"
        );
    loginBtn->setCursor(Qt::PointingHandCursor);

    connect(loginBtn,SIGNAL(clicked(bool)),this,SLOT(loginRedirect()));

    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginBtn);
    loginLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    mainVbox->addLayout(loginLayout);



}


Signup::~Signup()
{

}




void Signup::loginRedirect()
{
    this->hide();
    Login *login=new Login();
    login->show();
}

void Signup::signup()
{
   QString firstName= firstNameEdit->text().trimmed();
   QString lastName= lastNameEdit->text().trimmed();
   QString birthdate= birthDateEdit->date().toString().trimmed();
   QString userName= userNameEdit->text().trimmed();
   QString password= passwordEdit->text();

   if(firstName.isEmpty() || lastName.isEmpty() || birthdate.isEmpty() || userName.isEmpty() || password.isEmpty()){
       QMessageBox::warning(this,"Signup Failed","All input fields are obligatory");
       return;
    }

  QString hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

   if(Database::createUser(firstName,lastName,birthdate,userName,hashedPassword)){
      QMessageBox::information(this,"Signup success","signed up successfully , please Login");
       this->hide();
       Login *login=new Login();
       login->show();
   }else{
        QMessageBox::critical(this, "Error", "Failed to create account. Username may already exist.");
   }


}

bool Signup::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == birthDateEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            signupBtn->click();
            return true; // Event handled
        }
    }
    return QWidget::eventFilter(obj, event);
}









