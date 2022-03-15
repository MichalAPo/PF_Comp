#ifndef ASTAR_H
#define ASTAR_H

#include <math.h>
#include <limits>
#include "testwindow.h"
#include "structures.h"
#include "functions.h"

class astar: public functions
{
public:

    astar(testwindow*);
    astar() = delete;

    QList<IntVector> GetNeighbours(IntVector);
    QList<IntVector> ReconstructPath();
    IntVector CalculateOnBoardPosition(IntVector);
    void FindPath();
    float Heuristics(IntVector, IntVector);
    void Initialize();

    QList<IntVector> visitedCells;
    QList<IntVector> path;
    testwindow* windowPointer;
    OneCell board[boardSize][boardSize];
    IntVector startPos = IntVector(0,0);
    IntVector targetPos = IntVector(0,0);

};
#endif // ASTAR_H
