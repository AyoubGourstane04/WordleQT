#include "widget.h"
#include "login.h"
#include "database.h"





Widget::Widget(const QString &username, QWidget *parent)
    : QWidget(parent), currentUsername(username)
{
    setWindowTitle("Wordle");
    setWindowIcon(QIcon(":/res/w-solid.svg"));
    resize(500, 600);
    this->setStyleSheet(
        "background-color: #121212;"
        "color: #ffffff;"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);


    QHBoxLayout *headerLayout = new QHBoxLayout();


    QWidget *userInfoWidget = new QWidget();
    QHBoxLayout *userInfoLayout = new QHBoxLayout(userInfoWidget);
    userInfoLayout->setContentsMargins(0, 0, 0, 0);
    userInfoLayout->setSpacing(15);

    QString firstName = "";
    QString lastName = "";
    int score = 0;
    bool userLoggedIn = false;

    if(!currentUsername.isEmpty()){
        QVariantMap user = Database::getUserByUsername(this->currentUsername);
        firstName = user["firstName"].toString();
        lastName = user["lastName"].toString();
        score = user["score"].toInt();
        userLoggedIn = true;
    }

    if(userLoggedIn) {
       // QLabel *userIcon = new QLabel();
       // userIcon->setPixmap(QPixmap(":/res/user-regular.svg").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        QLabel *userNameLabel = new QLabel();
        userNameLabel->setText(QString("%1 %2").arg(firstName, lastName));
        userNameLabel->setFont(QFont("Futura", 12, QFont::Medium));
        userNameLabel->setStyleSheet("color: #bbbbbb;font-weight : bold;");

        scoreLabel = new QLabel();
        scoreLabel->setText(QString("Score: %1").arg(score));
        scoreLabel->setFont(QFont("Futura", 12, QFont::Medium));
        scoreLabel->setStyleSheet(
            "color: #4CAF50;"
            "background-color: rgba(76, 175, 80, 0.1);"
            "border-radius: 10px;"
            "padding: 3px 8px;"
            "font-weight : bold;"
            );

       // userInfoLayout->addWidget(userIcon);
        userInfoLayout->addWidget(userNameLabel);
        userInfoLayout->addWidget(scoreLabel);
        userInfoLayout->addStretch();
    }

    headerLayout->addWidget(userInfoWidget);
    headerLayout->addStretch();

    QPushButton *loginButton = new QPushButton(userLoggedIn ? "Logout" : "Login");
    loginButton->setFont(QFont("Futura", 12));
    loginButton->setStyleSheet(
        "QPushButton {"
        "color: #4a90e2;"
        "background: transparent;"
        "border: 1px solid #4a90e2;"
        "border-radius: 15px;"
        "font-weight: bold;"
        "padding: 5px 15px;"
        "min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "background-color: rgba(74, 144, 226, 0.1);"
        "}"
        );
    loginButton->setCursor(Qt::PointingHandCursor);
    connect(loginButton, SIGNAL(clicked(bool)), this, SLOT(loginRedirect()));

    headerLayout->addWidget(loginButton);
    mainLayout->addLayout(headerLayout);

    QLabel *titleLabel = new QLabel("WORDLE");
    titleLabel->setFont(QFont("Futura", 36, QFont::Bold));
    titleLabel->setStyleSheet(
        "color: #ffffff;"
        "letter-spacing: 2px;"
        "margin-bottom: 5px;"
        );
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);


    QLabel *subtitleLabel = new QLabel("Can you guess the word?");
    subtitleLabel->setFont(QFont("Futura", 14));
    subtitleLabel->setStyleSheet(
        "color: #bbbbbb;"
        "margin-bottom: 20px;"
        );
    subtitleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(subtitleLabel);


    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setVerticalSpacing(15);
    gridLayout->setHorizontalSpacing(8);
    gridLayout->setContentsMargins(30, 0, 30, 0);

    for(int row = 0; row < 6; row++) {
        for(int col = 0; col < 5; col++) {
            letterBoxes[row][col] = new QLineEdit(this);
            letterBoxes[row][col]->setMaxLength(1);
            letterBoxes[row][col]->setAlignment(Qt::AlignCenter);
            letterBoxes[row][col]->setFixedSize(50, 60);
            letterBoxes[row][col]->setFont(QFont("Futura", 20, QFont::Bold));
            letterBoxes[row][col]->setStyleSheet(
                "background-color: #1e1e1e;"
                "border: 2px solid #3a3a3a;"
                "color: white;"
                "border-radius: 5px;"
                "selection-background-color: #3a3a3a;"
                );

            letterBoxes[row][col]->setValidator(
                new QRegularExpressionValidator(QRegularExpression("[a-zA-Z]"), this)
                );

            gridLayout->addWidget(letterBoxes[row][col], row, col);
        }
    }
    mainLayout->addLayout(gridLayout);

    submitButton = new QPushButton("SUBMIT");
    submitButton->setFixedSize(150, 45);
    submitButton->setFont(QFont("Futura", 14, QFont::Bold));
    submitButton->setStyleSheet(
        "QPushButton {"
        "background-color: #4CAF50;"
        "color: white;"
        "border-radius: 8px;"
        "border: none;"
        "text-transform: uppercase;"
        "letter-spacing: 1px;"
        "}"
        "QPushButton:hover {"
        "background-color: #66BB6A;"
        "}"
        "QPushButton:pressed {"
        "background-color: #388E3C;"
        "}"
        );
    submitButton->setCursor(Qt::PointingHandCursor);
    submitButton->setDefault(true);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(submitButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    QString temp;
    do {
        temp = GenerateRandomWord();
    } while(!Exists(temp));
    targetWord = temp;

    // Connect events
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 5; ++col) {
            letterBoxes[row][col]->installEventFilter(
                new EnterKeyFilter([this]() {
                    submitButton->click();
                }, letterBoxes[row][col])
                );

            if(row == 0 && col == 0) letterBoxes[row][col]->setFocus();

            connect(letterBoxes[row][col], &QLineEdit::textChanged, [this, row, col](const QString &text) {
                if(text.isEmpty()) return;

                if(col < 4) {
                    letterBoxes[row][col+1]->setFocus();
                }

                if (!text.isEmpty()) {
                    letterBoxes[row][col]->setText(text.toUpper());
                }
            });
        }
    }


    connect(submitButton, &QPushButton::clicked, this, [this,&score](){ checkGuess(targetWord,score,currentUsername); });
}

Widget::~Widget() {}




bool Widget::isValid(const QString &word)
{
    if(word.length()!=WORD_LENGTH||word.isEmpty())return false;

    for(int i=0;i<word.length();i++){
        if(!word.at(i).isLetter()){
            return false;
        }
    }
    return true;
}


bool Widget::Exists(const QString &word)
{
    if(!isValid(word))return false;

    checkLoop = new QEventLoop(this);
    checkResult = false;

    QString Url="https://api.dictionaryapi.dev/api/v2/entries/en/" + word.toLower();

    QUrl url(Url);
    request.setUrl(url);

    manager = new QNetworkAccessManager(this);

    reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this,[this](){ handleReply(); });


    checkLoop->exec();

    delete checkLoop;
    checkLoop=nullptr;

    return checkResult;
}



void Widget::handleReply()
{
    if(reply->error()!=QNetworkReply::NoError){
        qDebug()<<"Network error : "<<reply->errorString();//prints messages to the console.
        checkResult=false;
    }else{
        int statusCode =reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        checkResult= (statusCode==200);//200->success
    }
    reply->deleteLater();
    if(checkLoop) checkLoop->quit();
}


QString Widget::GenerateRandomWord()
{
    QString Url="https://random-word-api.herokuapp.com/word?length=5";
    QUrl url(Url);

    request.setUrl(url);

    manager = new QNetworkAccessManager(this);

    reply = manager->get(request);

    QEventLoop loop;

    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if(reply->error()!= QNetworkReply::NoError){
        qDebug()<<"API Request failed:"<<reply->errorString();
            return QString();
    }

    QByteArray response = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(response);
    QJsonArray wordArray = doc.array();

    if(wordArray.isEmpty()){
        qDebug()<<"No word found";
        return QString();//like nullptr
    }

    QString Word = wordArray.first().toString();

    return Word;
}


void Widget::resetGame()
{
    for(int row=0; row<6; row++) {
        for(int col=0; col<5; col++) {
            letterBoxes[row][col]->clear();
            letterBoxes[row][col]->setEnabled(true);
            letterBoxes[row][col]->setStyleSheet(
                                        "background-color: #1e1e1e;"
                                        "border: 2px solid #3a3a3a;"
                                        "color: white;"
                                        "border-radius: 5px;"
                                        "selection-background-color: #3a3a3a;"
                                    );
        }
    }
    currentIndex=0;

    QString temp;

    do{
        temp=GenerateRandomWord();

    }while(!Exists(temp));

    targetWord=temp;

}

void Widget::animateTileReveal(QLineEdit *tile, const QString &style, int delay)
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(tile);
    tile->setGraphicsEffect(effect);

    QPropertyAnimation *fadeOut = new QPropertyAnimation(effect, "opacity");
    fadeOut->setDuration(150);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    fadeOut->setEasingCurve(QEasingCurve::InOutQuad);

    QPropertyAnimation *fadeIn = new QPropertyAnimation(effect, "opacity");
    fadeIn->setDuration(150);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setEasingCurve(QEasingCurve::InOutQuad);

    QTimer::singleShot(delay, [=]() {
        fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
        connect(fadeOut, &QPropertyAnimation::finished, [=]() {
            tile->setStyleSheet(style);
            fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
        });
    });
}




void Widget::checkGuess(QString target,int &score, const QString currentUsername)
{
    QString guess;


    for(int col=0;col<5;col++){
        guess+=letterBoxes[currentIndex][col]->text().toLower();
    }

    if(guess.length()!=5){
        QMessageBox::warning(this,"Error","the word must be 5 letters long !");
        return;
    }

    if(!Exists(guess)){
        QMessageBox::warning(this,"Error","the word provided is not a valid word !");
        return;
    }

    for(int col=0;col<5;col++){
        QChar guessLetter= guess.at(col);
        QString style;

        if(guessLetter==target.at(col)){
            style="background-color : green; color : white;";
        }else if(target.contains(guessLetter)){
            style="background-color : yellow; color : black;";
        }else{
            style="background-color : grey; color : white;";
        }
        style+=" border : 2px solid #565758; border-radius : 3px;";
        letterBoxes[currentIndex][col]->setEnabled(false);
        animateTileReveal(letterBoxes[currentIndex][col], style, col * 200);
    }

    if(guess==target){
       //QMessageBox::information(this,"Congratulations!","You Got the Word!!");
        QString str = "<div style='text-align: center; font-family: Futura, sans-serif;'>"
                      "<h2 style='color: #fff; font-size: 20px;'>Congratulations!</h2>"
                      "<span style='font-size: 35px; color: #4CAF50; font-weight: bold; "
                      "text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.6);'>You Got the Word!!</span>"
                      "<div style='font-size: 16px; color: #ddd; margin-top: 10px;'>"
                      "Well done, keep it up!</div></div>";

        qDebug() << "[DEBUG] Updating score for user:" << currentUsername << "Current score:" << score;

        Database::AlterScore(currentUsername);
        QVariantMap updatedUser = Database::getUserByUsername(currentUsername);
        score = updatedUser["score"].toInt();


        scoreLabel->setText(QString("Score: %1").arg(score));
        scoreLabel->setFont(QFont("Futura", 12, QFont::Medium));
        scoreLabel->setStyleSheet(
            "color: #4CAF50;"
            "background-color: rgba(76, 175, 80, 0.1);"
            "border-radius: 10px;"
            "padding: 3px 8px;"
            "font-weight : bold;"
            );



        QMessageBox::information(this, "Congratulations!", str);

        resetGame();
    }else if(++currentIndex>=6){
        //QString str= "The word was \t <span style='font-size : 25px; color: Green; font-weight: bold;'>" + target.toUpper()+" </span>";
        //QMessageBox::information(this,"Game Over!",str);
        QString str = "<div style='text-align: center; font-family: Futura, sans-serif;'>"
                      "<h2 style='color: #fff; font-size: 20px;'>The word was</h2>"
                      "<span style='font-size: 35px; color: #4CAF50; font-weight: bold; "
                      "text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.6);'>" + target.toUpper() + "</span>"
                                           "<div style='font-size: 16px; color: #ddd; margin-top: 10px;'>"
                                           "Better luck next time!</div></div>";

        QMessageBox::warning(this, "Game Over!", str);

        resetGame();
    }
}



void Widget::loginRedirect()
{
    this->hide();
    Login *login=new Login();
    login->show();
}


