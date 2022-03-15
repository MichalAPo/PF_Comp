#ifndef DFS_H
#define DFS_H

#include <math.h>
#include "testwindow.h"
#include "structures.h"
#include "functions.h"

class dfs: public functions
{
public:
    dfs(testwindow*);
    dfs() = delete;
    void Initialize();
    void FindPath(bool);
    QList<IntVector> ReconstructPath();

    testwindow* windowPointer;
    QList<IntVector> visitedCells;
    QList<IntVector> path;
    OneCell board[boardSize][boardSize];
    IntVector startPos = IntVector(0,0);
    IntVector targetPos = IntVector(0,0);

    bool test = true;
    QList<IntVector> checkedCells;
    IntVector currentCell;
};

#endif // DFS_H
