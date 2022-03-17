#include "astar.h"

using namespace utils;

astar::astar(IntVector bPos): pathfindingbase(bPos)
{
    path = std::list<IntVector>();
    visitedCells = std::list<IntVector>();
}

float astar::Heuristics(IntVector a, IntVector b)
{
    return sqrt((powf((a.x() - b.x()),2)) + (powf((a.y() - b.y()),2)));
}

std::list<IntVector> astar::GetNeighbours(IntVector position)
{
    std::list<IntVector> neighbours;

    for(int i=0; i<4; i++)
    {
        std::vector<IntVector> a = board[position.x()][position.y()].directions;
        IntVector p = position + board[position.x()][position.y()].directions[i];
        if (!IsInBounds(p, IntVector(0,0)))
            continue;
        if(board[p.x()][p.y()].type != CellType::Wall)
            neighbours.push_back(p);
    }
    return neighbours;
}

void astar::FindPath()
{
    Initialize();

    if(startPos == targetPos)
        return;

    if(!IsInBounds(startPos, IntVector(0,0))
            || !IsInBounds(targetPos, IntVector(0,0)))
        return;

    bool closedList[boardSize][boardSize];
    memset(closedList, false, sizeof(closedList));
    std::list<IntVector> openList;

    IntVector currentCell;
    board[startPos.x()][startPos.y()].f=0;
    board[startPos.x()][startPos.y()].g=0;
    board[startPos.x()][startPos.y()].h=0;
    board[startPos.x()][startPos.y()].parentPosition=startPos;
    openList.push_back(startPos);

    while(!openList.empty())
    {
        float fmin = std::numeric_limits<float>().max();
        for(auto it = openList.begin(); it !=openList.end(); ++it)
        {
            if(board[it->x()][it->y()].f < fmin)
            {
                currentCell = *it;
                closedList[it->x()][it->y()] = true;
                fmin = board[it->x()][it->y()].f;
            }
        }

        openList = ListRemove(openList, currentCell);

        std::list<IntVector> neighbours = GetNeighbours(currentCell);

        for(auto it = neighbours.begin(); it !=neighbours.end(); ++it)
        {
            int x=it->x();
            int y=it->y();
            if(!IsInBounds(*it, IntVector(0,0)))
                continue;
            if(*it == targetPos)
            {
                board[x][y].parentPosition=currentCell;
                path = ReconstructPath();
                return;
            }

            if(closedList[x][y])
                continue;

            float gThis = board[currentCell.x()][currentCell.y()].g + 1.0;
            float hThis = Heuristics(*it, targetPos);
            float fThis = gThis + hThis;

            if(board[x][y].f!=std::numeric_limits<float>().max() || board[x][y].f <= fThis)
                continue;

            openList.push_back(*it);
            board[x][y].ChangeGFH(gThis,fThis,hThis);
            board[x][y].parentPosition=currentCell;

            if(*it != startPos && *it != targetPos)
                visitedCells.push_back(*it);

        }
        closedList[currentCell.x()][currentCell.y()]=true;
    }
}

