#include "astar.h"
#include <limits>

bool operator ==(const OneCell l, const QList<OneCell>::Iterator r)
{
    return l.position.x() == r->position.x() && l.position.y() == r->position.y();
}

bool operator ==(const OneCell l, const OneCell r)
{
    return l.position.x() == r.position.x() && l.position.y() == r.position.y();
}


astar::astar(testwindow* window)
{
    windowPointer = window;
    path = QList<QVector2D>();
    visitedCells = QList<QVector2D>();
}

void astar::initialize()
{
    path.clear();
    visitedCells.clear();

    startPos = windowPointer->startPos;
    targetPos = windowPointer->targetPos;

    cells = QMap<QVector2D, OneCell>();

    QVector2D p;
    for(int y = 0; y<windowPointer->boardSize; y++)
    {
        for(int x = 0; x<windowPointer->boardSize; x++)
        {
            cells[QVector2D(x,y)] = OneCell(QVector2D(x,y));
            cells[QVector2D(x,y)].ChangeGFH(std::numeric_limits<float>().max(), std::numeric_limits<float>().max(), heuristics(p,targetPos));
        }
    }
    cells[startPos].ChangeGFH(0, 0, 0);
}

float astar::heuristics(QVector2D a, QVector2D b)
{
    return (abs(a.x()-b.x())+abs(a.y()-b.y()));
}

QList<OneCell> astar::getNeighbours(OneCell cell)
{
    QList<OneCell> neighbours;
    QVector2D offset[8]=
    {
      QVector2D(1,0),
      QVector2D(0,1),
      QVector2D(-1,0),
      QVector2D(0,-1),
      QVector2D(1,1),
      QVector2D(-1,-1),
      QVector2D(1,-1),
      QVector2D(-1,1)
    };

    for(int i=0; i<=7; i++)
    {
        QVector2D p = cell.position + offset[i];
        if (!IsInBounds(p, QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1)))
            continue;
        int boardIndex = p.x() + p.y() * windowPointer->boardSize;
        OneCell a = cells[p];
        if(windowPointer->board[boardIndex].type != CellType::Wall)
            neighbours.push_back(a);
    }
    return neighbours;
}

void astar::findPath()
{
    initialize();
    if(startPos == targetPos)
        return;
    if(!IsInBounds(startPos, QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1))
            || !IsInBounds(targetPos, QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1)))
        return;

    QVector<OneCell> closedList;
    QVector<OneCell> openList;

    OneCell currentCell = OneCell(QVector2D(0,0));

    openList.push_back(OneCell(startPos, CellType::Start));

    while(!openList.isEmpty())
    {
        float fmin = std::numeric_limits<float>().max();
        for(auto it = openList.begin(); it !=openList.end(); ++it)
        {
            if(it->f < fmin)
            {
                currentCell.position = it->position;
                fmin = it->f;
            }
        }

        openList.remove(openList.indexOf(currentCell));

        QList<OneCell> neighbours = getNeighbours(currentCell);

        for(auto it = neighbours.begin(); it !=neighbours.end(); ++it)
        {
            float gScoreEstimated = currentCell.g + heuristics(it->position, currentCell.position);

            if(gScoreEstimated > it->g)
                continue;

            it->CalculateF(gScoreEstimated, heuristics(it->position, targetPos));
            it->parentPosition = currentCell.position;

            if(!closedList.contains(it) && !openList.contains(it))
            {
                OneCell a = OneCell(it->position);

                a.ChangeGFH(it->g, it->f, it->h);
                a.parentPosition = it->parentPosition;
                openList.push_back(a);

                cells[it->position].CalculateF(gScoreEstimated, heuristics(it->position, targetPos));
                cells[it->position].parentPosition = currentCell.position;
            }
            else if(it->f < openList.value(openList.indexOf(it)).f)
            {
                OneCell a = OneCell(it->position);

                a.ChangeGFH(it->g, it->f, it->h);
                a.parentPosition = it->parentPosition;
                openList.replace(openList.indexOf(it),a);

                cells[it->position].CalculateF(gScoreEstimated, heuristics(it->position, targetPos));
                cells[it->position].parentPosition = currentCell.position;
            }

            if(it->position != startPos && it->position != targetPos && it->type != CellType::Wall)
                visitedCells.push_back(it->position);

            if(it->position == targetPos)
            {
                path = reconstructPath();
                return;
            }

        }
        closedList.push_back(currentCell);
    }
}

QList<QVector2D> astar::reconstructPath()
{
    QList<QVector2D> path = QList<QVector2D>();
    QVector2D pos = cells[targetPos].parentPosition;
    path.push_back(pos);

    while(pos != startPos)
    {
        pos = cells[pos].parentPosition;
        if(pos != startPos)
        {
            path.push_back(pos);
        }
    }
    return path;
}

void astar::drawPath(QList<QVector2D> path)
{
    for(auto it = path.begin(); it !=path.end(); ++it)
    {
            QVector2D a = QVector2D((it->x() * cellSize)+windowPointer->boardPosition.x(), (it->y() * cellSize)+windowPointer->boardPosition.y());
            windowPointer->changeOneCell(OneCell(a, CellType::Path), QColor(0,80,200,255));
    }
}

void astar::drawVisited(QList<QVector2D> visited)
{
    for(auto it = visited.begin(); it !=visited.end(); ++it)
    {
        QVector2D a = QVector2D((it->x() * cellSize)+windowPointer->boardPosition.x(), (it->y() * cellSize)+windowPointer->boardPosition.y());
        windowPointer->changeOneCell(OneCell(a, CellType::Visited), QColor(255,200,180,255));
    }
}


