#ifndef PATHFINDINGBASE_H
#define PATHFINDINGBASE_H

#include "structures.h"
#include "utils.h"
#include <list>
#include <set>

class pathfindingbase
{
public:
    pathfindingbase(IntVector, int seed);

    void CreateBoard(int seed);
    void Initialize();
    virtual void FindPath(){};
    virtual void FindPath(bool){};
    bool IsValid(IntVector);
    void GenerateMaze();
    std::list<IntVector> ReconstructPath();
    std::list<IntVector> GetNeighbours(IntVector);

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
};

#endif // PATHFINDINGBASE_H
