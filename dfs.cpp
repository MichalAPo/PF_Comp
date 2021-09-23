#include "dfs.h"

dfs::dfs(testwindow* window)
{
    this->windowPointer = window;
}


void dfs::Initialize()
{
    path.clear();
    visitedCells.clear();
    checkedCells.clear();

    startPos = windowPointer->startPos;
    targetPos = windowPointer->targetPos;
    currentCell = startPos;

    cells = QMap<QVector2D, OneCell>();

    for(int y = 0; y<windowPointer->boardSize; y++)
    {
        for(int x = 0; x<windowPointer->boardSize; x++)
        {
            int boardIndex = x + y * windowPointer->boardSize;
            cells[QVector2D(x,y)] = OneCell(QVector2D(x,y), windowPointer->board[boardIndex].type);
        }
    }
}

//dfs = 'd' -> dfs algorithm, dfs = 'b' bfs algorithm
void dfs::FindPath(char dfs)
{
    Initialize();

    if(startPos == targetPos)
        return;
    if(!IsInBounds(startPos, QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1))
            || !IsInBounds(targetPos, QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1)))
        return;

    checkedCells.push_back(currentCell);

    while(!checkedCells.isEmpty() && test)
    {
        switch (dfs)
        {
            case 'd':
            {
                currentCell = checkedCells.last();
                checkedCells.removeLast();
                break;
            }
            case 'b':
            {
                currentCell = checkedCells.first();
                checkedCells.removeFirst();
                break;
            }
        }

        if(currentCell == targetPos)
            break;

        for(int i=0; i<4; i++)
        {
            if(cells[currentCell + cells[currentCell].directions[i]].type != CellType::Wall
               && IsInBounds(currentCell + cells[currentCell].directions[i], QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1))
               && !checkedCells.contains(currentCell + cells[currentCell].directions[i])
               && !cells[currentCell + cells[currentCell].directions[i]].visited)
            {
                cells[currentCell + cells[currentCell].directions[i]].visited = true;
                checkedCells.push_back(currentCell + cells[currentCell].directions[i]);

                cells[currentCell + cells[currentCell].directions[i]].parentPosition = currentCell;

                if(currentCell + cells[currentCell].directions[i] != startPos && currentCell + cells[currentCell].directions[i] != targetPos)
                {
                    visitedCells.push_back(currentCell + cells[currentCell].directions[i]);
                }

                if((currentCell + cells[currentCell].directions[i]) == targetPos)
                {
                    path = ReconstructPath();
                    return;
                }

            }
        }
    }
}

QList<QVector2D> dfs::ReconstructPath()
{
    QVector2D pos = cells[targetPos].parentPosition;
    path.push_back(pos);

    while(pos != startPos && path.count() < 1000)
    {
        pos = cells[pos].parentPosition;
        if(pos != startPos)
        {
            path.push_back(pos);
        }
    }
    return path;
}

void dfs::DrawPath(QList<QVector2D> path)
{
    for(auto it = path.begin(); it !=path.end(); ++it)
    {
            QVector2D a = QVector2D((it->x() * cellSize)+windowPointer->boardPosition.x(), (it->y() * cellSize)+windowPointer->boardPosition.y());
            windowPointer->ChangeOneCell(OneCell(a, CellType::Path), QColor(0,80,200,255));
    }
}

void dfs::DrawVisited(QList<QVector2D> visited)
{
    for(auto it = visited.begin(); it !=visited.end(); ++it)
    {
        QVector2D a = QVector2D((it->x() * cellSize)+windowPointer->boardPosition.x(), (it->y() * cellSize)+windowPointer->boardPosition.y());
        windowPointer->ChangeOneCell(OneCell(a, CellType::Visited), QColor(255,200,180,255));
    }
}
