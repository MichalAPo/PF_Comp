#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "structures.h"
#include "cell.h"
#include "functions.h"

class testwindow: public QGraphicsRectItem, public functions
{
public:
    testwindow(QVector2D, int, QPainter*);
    void CreateBoard();
    void ChangeOneCell(QVector2D, QColor, CellType);
    void TypeText(QVector2D, QString);
    void DrawBoard();
    void ClearPath();
    void Clear();

    QVector2D boardPosition;
    int boardSize=1;
    QPainter* paintPointer;
    //QList<OneCell> board;
    QMap<QVector2D, OneCell> board;
    QVector2D startPos = QVector2D(-1,-1);
    QVector2D targetPos = QVector2D(-1,-1);
};

#endif // TESTWINDOW_Hs
