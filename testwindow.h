#ifndef TESTWINDOW_H
#define TESTWINDOW_H
#include "structures.h"
#include "cell.h"
#include "functions.h"
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>

class testwindow: public QGraphicsRectItem, public functions
{
public:
    testwindow(QVector2D, int, QPainter*);
    void createBoard();
    void changeOneCell(OneCell, QColor);
    void drawBoard();
    void clearPath();
    QVector2D boardPosition;
    int boardSize=1;
    QPainter* paintPointer;
    QList<OneCell> board;
    QVector2D startPos = QVector2D(-1,-1);
    QVector2D targetPos = QVector2D(-1,-1);
    void clear();
};

#endif // TESTWINDOW_Hs
