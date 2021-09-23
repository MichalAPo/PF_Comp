#ifndef DFS_H
#define DFS_H

#include <math.h>
#include <QVector2D>
#include "testwindow.h"
#include "structures.h"
#include "functions.h"

class dfs: public functions
{
public:
    dfs(testwindow*);
    dfs() = delete;
    void Initialize();
    void FindPath(char);
    void DrawPath(QList<QVector2D>);
    void DrawVisited(QList<QVector2D>);
    QList<QVector2D> ReconstructPath();

    testwindow* windowPointer;
    QList<QVector2D> visitedCells;
    QList<QVector2D> path;
    QMap<QVector2D, OneCell> cells;
    QVector2D startPos = QVector2D(0,0);
    QVector2D targetPos = QVector2D(0,0);

    bool test = true;
    QList<QVector2D> checkedCells;
    QVector2D currentCell;
};

#endif // DFS_H
