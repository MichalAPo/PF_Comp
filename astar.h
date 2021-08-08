#ifndef ASTAR_H
#define ASTAR_H

#include "testwindow.h"
#include "structures.h"
#include "functions.h"
#include <math.h>
#include <QVector2D>

class astar: public functions
{
public:

    astar(testwindow*);
    QList<OneCell> getNeighbours(OneCell);
    QList<QVector2D> reconstructPath();
    void findPath();
    float heuristics(QVector2D, QVector2D);
    void initialize();
    void drawPath(QList<QVector2D>);
    void drawVisited(QList<QVector2D>);
    QVector2D calculateOnBoardPosition(QVector2D);

    QList<QVector2D> visitedCells;
    QList<QVector2D> path;
    testwindow* windowPointer;
    QMap<QVector2D, OneCell> cells;
    QVector2D startPos = QVector2D(0,0);
    QVector2D targetPos = QVector2D(0,0);

};
#endif // ASTAR_H
