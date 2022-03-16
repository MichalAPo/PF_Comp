#ifndef DFS_H
#define DFS_H

#include <math.h>
#include "pathfindingbase.h"
#include "structures.h"
#include "utils.h"

class dfs: public pathfindingbase
{
public:
    dfs(IntVector);
    bool test = true;
    void FindPath(bool) override;
};

#endif // DFS_H
