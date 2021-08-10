#ifndef DFS_H
#define DFS_H
#include "testwindow.h"
#include "structures.h"
#include "functions.h"
#include <math.h>
#include <QVector2D>

class dfs: public functions
{
public:
    dfs(testwindow*);
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
};

#endif // DFS_H
