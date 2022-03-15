#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "structures.h"
#include "functions.h"
#include "testwindow.h"
#include "GenerateMaze.h"

class DrawManager: public functions
{
public:
    DrawManager(QPainter*);
    void DrawPath(QList<IntVector>);
    void DrawVisited(QList<IntVector>);
    void ChangeOneCell(testwindow*, IntVector, QColor, CellType);
    void TypeText(IntVector, QString);
    void DrawBoard(testwindow*);
    void ClearPath(testwindow*);
    void Clear(testwindow*);
    void DrawMaze(testwindow*, GenerateMaze*);
    QPainter* paintPointer;
};

#endif // DRAWMANAGER_H
