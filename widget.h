#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QGridLayout>
#include<QLabel>
#include<QHBoxLayout>
#include<QMessageBox>
#include<QPushButton>
#include<QLineEdit>
#include<QObject>
#include<array>
#include<QRegularExpression>
#include<QRegularExpressionValidator>
#include<QMessageBox>
#include<QEventLoop>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkReply>
#include<QtNetwork/QNetworkRequest>
#include<QUrl>
#include<QDebug>
#include<QFile>
#include<QStringList>
#include<QTextStream>
#include<QRandomGenerator>
#include<QJsonDocument>
#include<QJsonArray>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include<QTimer>
#include<QObject>
#include<QEvent>
#include<QKeyEvent>
#include<QMap>
#include<QJsonObject>


const int WORD_LENGTH = 5;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(const QString& username="",QWidget *parent = nullptr);
    ~Widget();
    bool Exists(const QString&);
    bool isValid(const QString&);
    void resetGame();
    QString GenerateRandomWord();
    QStringList GetWordList(const QString&);
    void animateTileReveal(QLineEdit*, const QString &, int);
private:
    //std::array<std::array<QLineEdit*, 5>, 6> letterBoxes;
      QLineEdit* letterBoxes[6][5];
      int currentIndex=0;
      QEventLoop* checkLoop = nullptr;
      bool checkResult = false;
      QNetworkReply* reply;
      QNetworkAccessManager *manager;
      QNetworkRequest request;
      QString targetWord;
      QPushButton *submitButton;
      QString currentUsername;
      QLabel *scoreLabel;



    public slots :
      void checkGuess(QString,int&,const QString);
      void handleReply();
      void loginRedirect();

};

//submit on pressing enter
class EnterKeyFilter : public QObject {
    Q_OBJECT
public:
    EnterKeyFilter(std::function<void()> submitFunc, QObject *parent = nullptr)
        : QObject(parent), submitCallback(std::move(submitFunc)) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
                if (submitCallback) submitCallback();
                return true;
            }
        }
        return QObject::eventFilter(obj, event);
    }

private:
    std::function<void()> submitCallback;
};







#endif // WIDGET_H
