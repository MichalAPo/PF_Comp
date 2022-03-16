#include "astar.h"

using namespace utils;

astar::astar(IntVector bPos): pathfindingbase(bPos)
{
    path = QList<IntVector>();
    visitedCells = QList<IntVector>();
}

float astar::Heuristics(IntVector a, IntVector b)
{
    return sqrt((powf((a.x() - b.x()),2)) + (powf((a.y() - b.y()),2)));
}

QList<IntVector> astar::GetNeighbours(IntVector position)
{
    QList<IntVector> neighbours;

    for(int i=0; i<4; i++)
    {
        IntVector p = position + board[position.x()][position.y()].directions[i];
        if (!IsInBounds(p, IntVector(0,0)))
            continue;
        //int boardIndex = p.x() + p.y() * windowPointer->boardSize;
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

    QVector<IntVector> closedList;
    QVector<IntVector> openList;

    IntVector currentCell;

    openList.push_back(startPos);

    while(!openList.isEmpty())
    {
        float fmin = std::numeric_limits<float>().max();
        for(auto it = openList.begin(); it !=openList.end(); ++it)
        {
            if(board[it->x()][it->y()].f < fmin)
            {
                currentCell = *it;
                fmin = board[it->x()][it->y()].f;
            }
        }

        openList.remove(openList.indexOf(currentCell));

        QList<IntVector> neighbours = GetNeighbours(currentCell);

        for(auto it = neighbours.begin(); it !=neighbours.end(); ++it)
        {
            float gScoreEstimated = board[currentCell.x()][currentCell.y()].g + Heuristics(*it, currentCell);

            if(gScoreEstimated > board[it->x()][it->y()].g)
                continue;

            board[it->x()][it->y()].CalculateF(gScoreEstimated, Heuristics(*it, targetPos));
            board[it->x()][it->y()].parentPosition = currentCell;

           // if(openList.contains(it))
                //if(cells[*it].f > openList.at(openList.indexOf(it)).f)
                    //continue;

            //if(closedList.contains(it))
                //if(it->f > closedList.at(closedList.indexOf(it)).f)
                    //continue;

            //OneCell a = OneCell(it->position);
            //a.ChangeGFH(it->g, it->f, it->h);
            //a.parentPosition = it->parentPosition;
            openList.push_back(*it);

            board[it->x()][it->y()].CalculateF(gScoreEstimated, Heuristics(*it, targetPos));
            board[it->x()][it->y()].parentPosition = currentCell;

            if(*it != startPos && *it != targetPos)
                visitedCells.push_back(*it);

            if(*it == targetPos)
            {
                path = ReconstructPath();
                return;
            }

        }
        closedList.push_back(currentCell);
    }
}

