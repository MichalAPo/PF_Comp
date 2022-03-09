#ifndef ASTAR_H
#define ASTAR_H

#include <math.h>
#include <QVector2D>
#include <limits>
#include "testwindow.h"
#include "structures.h"
#include "functions.h"

class astar: public functions
{
public:

    astar(testwindow*);
    astar() = delete;

    QList<OneCell> GetNeighbours(QVector2D);
    QList<QVector2D> ReconstructPath();
    QVector2D CalculateOnBoardPosition(QVector2D);
    void FindPath();
    float Heuristics(QVector2D, QVector2D);
    void Initialize();
    void DrawPath(QList<QVector2D>);
    void DrawVisited(QList<QVector2D>);

    QList<QVector2D> visitedCells;
    QList<QVector2D> path;
    testwindow* windowPointer;
    QMap<QVector2D, OneCell> cells;
    QVector2D startPos = QVector2D(0,0);
    QVector2D targetPos = QVector2D(0,0);

};
#endif // ASTAR_H
