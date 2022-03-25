#include "astar.h"

using namespace utils;

float astar::Heuristics(IntVector a, IntVector b)
{
    return sqrt((powf((a.x - b.x),2)) + (powf((a.y - b.y),2)));
}

void astar::FindPath()
{
    if(startPos == targetPos)
        return;

    if(!IsInBounds(startPos, IntVector(0,0))
            || !IsInBounds(targetPos, IntVector(0,0)))
        return;

    Initialize();

    bool closedCells[boardSize][boardSize];
    memset(closedCells, false, sizeof(closedCells));
    std::list<IntVector> openList;

    IntVector currentCell;
    board[startPos.x][startPos.y].f=0;
    board[startPos.x][startPos.y].g=0;
    board[startPos.x][startPos.y].h=0;
    board[startPos.x][startPos.y].parentPosition=startPos;
    //board[startPos.x()][startPos.y()] = {0, 0, 0, startPos};
    openList.push_back(startPos);

    while(!openList.empty())
    {
        float fmin = std::numeric_limits<float>().max();
        for(auto it = openList.begin(); it !=openList.end(); ++it)
        {
            if(board[it->x][it->y].f < fmin)
            {
                currentCell = *it;
                closedCells[it->x][it->y] = true;
                fmin = board[it->x][it->y].f;
            }
        }

        openList = RemoveVectorElement(openList, currentCell);

        std::list<IntVector> neighbours = GetNeighbours(currentCell);

        for(auto it = neighbours.begin(); it !=neighbours.end(); ++it)
        {
            int x=it->x;
            int y=it->y;
            if(!IsInBounds(*it, IntVector(0,0)))
                continue;
            if(*it == targetPos)
            {
                board[x][y].parentPosition=currentCell;
                path = ReconstructPath();
                return;
            }

            if(closedCells[x][y])
                continue;

            float NeighbourG = board[currentCell.x][currentCell.y].g + 1.0;
            float NeighbourH = Heuristics(*it, targetPos);
            float NeighbourF = NeighbourG + NeighbourH + board[it->x][it->y].travelCost;
//            float NeighbourF = NeighbourG + NeighbourH;

            if(board[x][y].f != std::numeric_limits<float>().max() || board[x][y].f <= NeighbourF)
                continue;

            openList.push_back(*it);
            board[x][y].ChangeFGH(NeighbourF,NeighbourG,NeighbourH);
            board[x][y].parentPosition=currentCell;

            if(*it != startPos && *it != targetPos && !board[x][y].visited)
            {
                board[x][y].visited=true;
                visitedCells.push_back(*it);
            }

        }
        closedCells[currentCell.x][currentCell.y]=true;
    }
}

