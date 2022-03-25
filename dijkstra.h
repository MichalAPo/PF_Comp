#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "structures.h"
#include "utils.h"
#include "pathfindingbase.h"

class dijkstra: public pathfindingbase
{
public:
    dijkstra(IntVector bPos, int seed): pathfindingbase(bPos, seed){};
    void FindPath() override;
};

#endif // DIJKSTRA_H
