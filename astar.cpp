#include "astar.h"

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
    this->windowPointer = window;
    path = QList<QVector2D>();
    visitedCells = QList<QVector2D>();
}

void astar::Initialize()
{
    path.clear();
    visitedCells.clear();

    startPos = windowPointer->startPos;
    targetPos = windowPointer->targetPos;

    cells = QMap<QVector2D, OneCell>();

    for(int y = 0; y<windowPointer->boardSize; y++)
    {
        for(int x = 0; x<windowPointer->boardSize; x++)
        {
            cells[QVector2D(x,y)] = OneCell(QVector2D(x,y));
            cells[QVector2D(x,y)].ChangeGFH(std::numeric_limits<float>().max(), std::numeric_limits<float>().max(), std::numeric_limits<float>().max());
        }
    }
    cells[startPos].ChangeGFH(0, 0, 0);
}

float astar::Heuristics(QVector2D a, QVector2D b)
{
    return sqrt((powf((a.x() - b.x()),2)) + (powf((a.y() - b.y()),2)));
}

QList<OneCell> astar::GetNeighbours(OneCell cell)
{
    QList<OneCell> neighbours;

    for(int i=0; i<4; i++)
    {
        QVector2D p = cell.position + cells[cell.position].directions[i];
        if (!IsInBounds(p, QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1)))
            continue;
        int boardIndex = p.x() + p.y() * windowPointer->boardSize;
        OneCell a = cells[p];
        if(windowPointer->board[boardIndex].type != CellType::Wall)
            neighbours.push_back(a);
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

    QVector<OneCell> closedList;
    QVector<OneCell> openList;

    OneCell currentCell;

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

        QList<OneCell> neighbours = GetNeighbours(currentCell);

        for(auto it = neighbours.begin(); it !=neighbours.end(); ++it)
        {
            float gScoreEstimated = currentCell.g + Heuristics(it->position, currentCell.position);

            if(gScoreEstimated > it->g)
                continue;

            it->CalculateF(gScoreEstimated, Heuristics(it->position, targetPos));
            it->parentPosition = currentCell.position;

            if(openList.contains(it))
                if(it->f > openList.at(openList.indexOf(it)).f)
                    continue;

            if(closedList.contains(it))
                if(it->f > closedList.at(closedList.indexOf(it)).f)
                    continue;

            OneCell a = OneCell(it->position);
            a.ChangeGFH(it->g, it->f, it->h);
            a.parentPosition = it->parentPosition;
            openList.push_back(a);

            cells[it->position].CalculateF(gScoreEstimated, Heuristics(it->position, targetPos));
            cells[it->position].parentPosition = currentCell.position;

            if(it->position != startPos && it->position != targetPos)
                visitedCells.push_back(it->position);

            if(it->position == targetPos)
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
            QVector2D a = QVector2D((it->x() * cellSize)+windowPointer->boardPosition.x(), (it->y() * cellSize)+windowPointer->boardPosition.y());
            windowPointer->ChangeOneCell(OneCell(a, CellType::Path), QColor(0,80,200,255));
    }
}

void astar::DrawVisited(QList<QVector2D> visited)
{
    for(auto it = visited.begin(); it !=visited.end(); ++it)
    {
        QVector2D a = QVector2D((it->x() * cellSize)+windowPointer->boardPosition.x(), (it->y() * cellSize)+windowPointer->boardPosition.y());
        windowPointer->ChangeOneCell(OneCell(a, CellType::Visited), QColor(255,200,180,255));
    }
}


