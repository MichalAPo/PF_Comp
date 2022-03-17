#include "dfs.h"
#include "QDebug"

using namespace utils;

void dfs::FindPath(bool dfs)
{
    Initialize();
    board[targetPos.x()][targetPos.y()].visited = false;

    if(startPos == targetPos)
        return;
    if(!IsInBounds(startPos, IntVector(0,0))
            || !IsInBounds(targetPos, IntVector(0,0)))
        return;

    currentCell = startPos;
    checkedCells.push_back(currentCell);

    while(!checkedCells.empty() && test)
    {
        switch (dfs)
        {
            case true:
            {
                currentCell = checkedCells.back();
                checkedCells.pop_back();
                break;
            }
            case false:
            {
                currentCell = checkedCells.front();
                checkedCells.pop_front();
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
            if (ListContains(checkedCells, index))
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
