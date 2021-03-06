#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "structures.h"
#include "utils.h"
#include "pathfindingbase.h"

class drawmanager
{
public:
    drawmanager(QPainter*);
    void DrawPath(pathfindingbase*);
    void DrawVisited(pathfindingbase*);
    void ChangeOneCell(pathfindingbase*, IntVector, QColor, CellType);
    void TypeText(IntVector, QString);
    void DrawBoard(pathfindingbase*, QString);
    void ClearPath(pathfindingbase*);
    void Clear(pathfindingbase*);
    void DrawMaze(pathfindingbase*, pathfindingbase*);
    QPainter* paintPointer;

    void DrawTags(pathfindingbase*);
};

#endif // DRAWMANAGER_H
