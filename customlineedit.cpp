#include "customlineedit.h"
#include <QKeyEvent>

CustomLineEdit::CustomLineEdit(QWidget *parent)
    : QLineEdit(parent), row(0), col(0)
{
}

void CustomLineEdit::setGridPosition(int r, int c)
{
    row = r;
    col = c;
}

int CustomLineEdit::getRow() const { return row; }
int CustomLineEdit::getCol() const { return col; }

void CustomLineEdit::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        emit arrowKeyPressed(row, col - 1);
        return;
    case Qt::Key_Right:
        emit arrowKeyPressed(row, col + 1);
        return;
    case Qt::Key_Up:
        emit arrowKeyPressed(row - 1, col);
        return;
    case Qt::Key_Down:
        emit arrowKeyPressed(row + 1, col);
        return;
    default:
        break;
    }

    QLineEdit::keyPressEvent(event);
}
