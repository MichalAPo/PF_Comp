#ifndef PATHFINDINGBASE_H
#define PATHFINDINGBASE_H

#include "structures.h"
#include "utils.h"

class pathfindingbase
{
public:
    pathfindingbase(IntVector);

    void CreateBoard();
    void Initialize();
    virtual void FindPath(){};
    virtual void FindPath(bool){};
    bool IsValid(IntVector);
    void GenerateMaze();
    QList<IntVector> ReconstructPath();

    IntVector boardPosition;
    QList<IntVector> visitedCells;
    QList<IntVector> path;
    OneCell board[boardSize][boardSize];
    OneCell maze[boardSize][boardSize];
    IntVector startPos;
    IntVector targetPos;
    QList<IntVector> checkedCells;
    IntVector currentCell;
    QList<IntVector> mazePaths;
    IntVector checkCell;
};

#endif // PATHFINDINGBASE_H
