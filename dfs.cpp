#include "dfs.h"
#include "QDebug"

dfs::dfs(testwindow* window)
{
    this->windowPointer = window;
}


void dfs::Initialize()
{
    path.clear();
    visitedCells.clear();
    checkedCells.clear();
    cells.clear();

    startPos = windowPointer->startPos;
    targetPos = windowPointer->targetPos;
    currentCell = startPos;

    cells = QMap<QVector2D, OneCell>();

    for(int y = 0; y<windowPointer->boardSize; y++)
        for(int x = 0; x<windowPointer->boardSize; x++)
            cells[QVector2D(x,y)] = OneCell(QVector2D(x,y));
}

//dfs = true -> dfs algorithm, dfs = false bfs algorithm
void dfs::FindPath(bool dfs)
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
            case true:
            {
                currentCell = checkedCells.last();
                checkedCells.removeLast();
                break;
            }
            case false:
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
            QVector2D index = (currentCell + cells[currentCell].directions[i]);
            if(windowPointer->board[index].type == CellType::Wall)
                continue;
            if (!IsInBounds(index, QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1)))
                continue;
            if (checkedCells.contains(index))
                continue;
            if (cells[index].visited)
                continue;

            cells[index].visited = true;
            checkedCells.push_back(index);

            cells[index].parentPosition = currentCell;

            if(currentCell + cells[currentCell].directions[i] != startPos && currentCell + cells[currentCell].directions[i] != targetPos)
                visitedCells.push_back(currentCell + cells[currentCell].directions[i]);

            if((currentCell + cells[currentCell].directions[i]) == targetPos)
            {
                path = ReconstructPath();
                return;
            }
        }
    }
}

QList<QVector2D> dfs::ReconstructPath()
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

void dfs::DrawPath(QList<QVector2D> path)
{
    for(auto it = path.begin(); it !=path.end(); ++it)
    {
            QVector2D currentCell = QVector2D((it->x() * cellSize)+windowPointer->boardPosition.x(), (it->y() * cellSize)+windowPointer->boardPosition.y());
            windowPointer->ChangeOneCell(OneCell(currentCell, CellType::Path), QColor(0,80,200,255));
            //windowPointer->TypeText(currentCell, QString::number(cells[QVector2D(it->x(),it->y())].parentPosition.x())+","+QString::number(cells[QVector2D(it->x(),it->y())].parentPosition.y()));
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
