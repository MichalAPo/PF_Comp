#include "dfs.h"
#include "QDebug"

using namespace utils;

dfs::dfs(IntVector bPos): pathfindingbase(bPos)
{
}

void dfs::FindPath(bool dfs)
{
    Initialize();

    if(startPos == targetPos)
        return;
    if(!IsInBounds(startPos, IntVector(0,0))
            || !IsInBounds(targetPos, IntVector(0,0)))
        return;

    currentCell = startPos;
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
            IntVector offset = board[currentCell.x()][currentCell.y()].directions[i];
            IntVector index = (currentCell + board[currentCell.x()][currentCell.y()].directions[i]);
            if(board[index.x()][index.y()].type == CellType::Wall)
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
