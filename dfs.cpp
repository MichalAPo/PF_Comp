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
    //cells.clear();

    startPos = windowPointer->startPos;
    targetPos = windowPointer->targetPos;
    currentCell = startPos;

    //cells = QMap<IntVector, OneCell>();

    for(int y = 0; y<boardSize; y++){
        for(int x = 0; x<boardSize; x++){
            board[x][y] = OneCell(CellType::Empty);
        }
    }
}

//dfs = true -> dfs algorithm, dfs = false bfs algorithm
void dfs::FindPath(bool dfs)
{
    Initialize();

    if(startPos == targetPos)
        return;
    if(!IsInBounds(startPos, IntVector(0,0))
            || !IsInBounds(targetPos, IntVector(0,0)))
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
            IntVector index = (currentCell + board[currentCell.x()][currentCell.y()].directions[i]);
            if(windowPointer->board[index.x()][index.y()].type == CellType::Wall)
                continue;
            if (!IsInBounds(index, IntVector(0,0)))
                continue;
            if (checkedCells.contains(index))
                continue;
            if (board[index.x()][index.y()].visited)
                continue;

            board[index.x()][index.y()].visited = true;
            checkedCells.push_back(index);

            board[index.x()][index.y()].parentPosition = currentCell;

            if(currentCell + board[currentCell.x()][currentCell.y()].directions[i] != startPos
                    && currentCell + board[currentCell.x()][currentCell.y()].directions[i] != targetPos)
                visitedCells.push_back(currentCell + board[currentCell.x()][currentCell.y()].directions[i]);

            if((currentCell + board[currentCell.x()][currentCell.y()].directions[i]) == targetPos)
            {
                path = ReconstructPath();
                return;
            }
        }
    }
}

QList<IntVector> dfs::ReconstructPath()
{
    QList<IntVector> path = QList<IntVector>();
    IntVector pos = board[targetPos.x()][targetPos.y()].parentPosition;
    path.push_back(pos);

    while(pos != startPos)
    {
        pos = board[pos.x()][pos.y()].parentPosition;

        if(pos != startPos)
        {
            path.push_back(pos);
        }
    }
    return path;
}
