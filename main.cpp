#include "widget.h"
#include "database.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!Database::initializeDatabase()) {
        qDebug() << "Database initialization failed!";
        return -1;
    }

    Widget w;

    w.show();
    return a.exec();
}
