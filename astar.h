#ifndef ASTAR_H
#define ASTAR_H

#include <math.h>
#include <limits>
#include "structures.h"
#include "utils.h"
#include "pathfindingbase.h"

class astar: public pathfindingbase
{
public:

    astar(IntVector);
    QList<IntVector> GetNeighbours(IntVector);
    float Heuristics(IntVector, IntVector);
    void FindPath() override;
};
#endif // ASTAR_H
