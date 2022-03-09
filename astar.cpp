#include "astar.h"

astar::astar(testwindow* window)
{
    this->windowPointer = window;
    path = QList<QVector2D>();
    visitedCells = QList<QVector2D>();
}

void astar::Initialize()
{
    path.clear();
    visitedCells.clear();
    cells.clear();

    startPos = windowPointer->startPos;
    targetPos = windowPointer->targetPos;

    cells = QMap<QVector2D, OneCell>();

    for(int y = 0; y<windowPointer->boardSize; y++)
    {
        for(int x = 0; x<windowPointer->boardSize; x++)
        {
            cells[QVector2D(x,y)] = OneCell(CellType::Empty);
            cells[QVector2D(x,y)].ChangeGFH(std::numeric_limits<float>().max(), std::numeric_limits<float>().max(), std::numeric_limits<float>().max());
        }
    }
    //cells[startPos].type=CellType::Start;
}

float astar::Heuristics(QVector2D a, QVector2D b)
{
    return sqrt((powf((a.x() - b.x()),2)) + (powf((a.y() - b.y()),2)));
}

QList<QVector2D> astar::GetNeighbours(QVector2D position)
{
    QList<QVector2D> neighbours;

    for(int i=0; i<4; i++)
    {
        QVector2D p = position + cells[position].directions[i];
        if (!IsInBounds(p, QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1)))
            continue;
        //int boardIndex = p.x() + p.y() * windowPointer->boardSize;
        if(windowPointer->board[p].type != CellType::Wall)
            neighbours.push_back(p);
    }
    return neighbours;
}

void astar::FindPath()
{
    Initialize();

    if(startPos == targetPos)
        return;

    if(!IsInBounds(startPos, QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1))
            || !IsInBounds(targetPos, QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1)))
        return;

    QVector<QVector2D> closedList;
    QVector<QVector2D> openList;

    QVector2D currentCell;

    openList.push_back(startPos);

    while(!openList.isEmpty())
    {
        float fmin = std::numeric_limits<float>().max();
        for(auto it = openList.begin(); it !=openList.end(); ++it)
        {
            if(cells[*it].f < fmin)
            {
                currentCell = *it;
                fmin = cells[*it].f;
            }
        }

        openList.remove(openList.indexOf(currentCell));

        QList<QVector2D> neighbours = GetNeighbours(currentCell);

        for(auto it = neighbours.begin(); it !=neighbours.end(); ++it)
        {
            float gScoreEstimated = cells[currentCell].g + Heuristics(*it, currentCell);

            if(gScoreEstimated > cells[*it].g)
                continue;

            cells[*it].CalculateF(gScoreEstimated, Heuristics(*it, targetPos));
            cells[*it].parentPosition = currentCell;

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

            cells[*it].CalculateF(gScoreEstimated, Heuristics(*it, targetPos));
            cells[*it].parentPosition = currentCell;

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

QList<QVector2D> astar::ReconstructPath()
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

void astar::DrawPath(QList<QVector2D> path)
{
    for(auto it = path.begin(); it !=path.end(); ++it)
    {
            QVector2D currentCell = QVector2D((it->x() * cellSize)+windowPointer->boardPosition.x(), (it->y() * cellSize)+windowPointer->boardPosition.y());
            windowPointer->ChangeOneCell(currentCell, QColor(0,80,200,255), CellType::Path);
            //windowPointer->TypeText(currentCell, QString::number(cells[QVector2D(it->x(),it->y())].parentPosition.x())+","+QString::number(cells[QVector2D(it->x(),it->y())].parentPosition.y()));
    }
}

void astar::DrawVisited(QList<QVector2D> visited)
{
    for(auto it = visited.begin(); it !=visited.end(); ++it)
    {
        QVector2D currentCell = QVector2D((it->x() * cellSize)+windowPointer->boardPosition.x(), (it->y() * cellSize)+windowPointer->boardPosition.y());
        windowPointer->ChangeOneCell(currentCell, QColor(255,200,180,255), CellType::Visited);
    }
}


