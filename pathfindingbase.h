#ifndef PATHFINDINGBASE_H
#define PATHFINDINGBASE_H

#include "structures.h"
#include "utils.h"
#include <list>
#include <set>

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
    std::list<IntVector> ReconstructPath();

    IntVector boardPosition;
    std::list<IntVector> visitedCells;
    std::list<IntVector> path;
    OneCell board[boardSize][boardSize];
    OneCell maze[boardSize][boardSize];
    IntVector startPos;
    IntVector targetPos;
    std::list<IntVector> checkedCells;
    IntVector currentCell;
    std::list<IntVector> mazePaths;
    IntVector checkCell;
};

#endif // PATHFINDINGBASE_H
