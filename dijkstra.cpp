#include "dijkstra.h"

using namespace utils;

void dijkstra::FindPath()
{
    if(startPos == targetPos)
        return;

    if(!IsInBounds(startPos, IntVector(0,0))
            || !IsInBounds(targetPos, IntVector(0,0)))
        return;

    Initialize();
    currentCell = startPos;
    board[startPos.x][startPos.y].f=0;
    board[startPos.x][startPos.y].visited=true;
    std::list<IntVector> openList;
    openList.push_back(currentCell);
    IntVector nextCell;

    while(currentCell != targetPos)
    {
        if(openList.empty())
            return;
        openList = RemoveVectorElement(openList, currentCell);

        std::list<IntVector> neighbours = GetNeighbours(currentCell);
        openList.insert(openList.end(),neighbours.begin(),neighbours.end());
        float smallestF=std::numeric_limits<float>().max();

        for(auto it = openList.begin(); it !=openList.end(); ++it)
        {
            if(*it==targetPos)
            {
                board[it->x][it->y].parentPosition = currentCell;
                path = ReconstructPath();
                return;
            }

            if(!board[it->x][it->y].visited)
            {
                visitedCells.push_back(*it);
                board[it->x][it->y].parentPosition = currentCell;
                board[it->x][it->y].visited=true;
            }

            if(board[currentCell.x][currentCell.y].f + board[it->x][it->y].travelCost < board[it->x][it->y].f)
                board[it->x][it->y].f = board[currentCell.x][currentCell.y].f + board[it->x][it->y].travelCost;

            if(smallestF <= board[it->x][it->y].f)
                continue;
            smallestF = board[it->x][it->y].f;
            nextCell = *it;
        }
        currentCell = nextCell;
    }
    path = ReconstructPath();
}
