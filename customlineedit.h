#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit CustomLineEdit(QWidget *parent = nullptr);

    void setGridPosition(int row, int col);
    int getRow() const;
    int getCol() const;

signals:
    void arrowKeyPressed(int newRow, int newCol);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    int row, col;
};

#endif // CUSTOMLINEEDIT_H
