#include "GenerateMaze.h"

GenerateMaze::GenerateMaze(testwindow* window)
{
    windowPointer = window;
}

void GenerateMaze::Initialize()
{
    firstTime = false;
    pathCells = QList<IntVector>();
    //maze.clear();

    for(int y=0; y<boardSize; y++)
    {
        for(int x=0; x<boardSize; x++)
        {
            board[x][y] = OneCell(CellType::Wall);
        }
    }

    IntVector firstCell = IntVector(1, 1);

    board[firstCell.x()][firstCell.y()].type = CellType::Empty;
    checkCell = firstCell;
    pathCells.push_back(checkCell);
}

bool GenerateMaze::IsValid(IntVector pos)
{
    IntVector offset[9] =
    {
        IntVector(1,0),
        IntVector(0,1),
        IntVector(0,-1),
        IntVector(1,-1),
        IntVector(1,1),
        IntVector(-1,-1),
        IntVector(-1,1),
        IntVector(-1,0),
        IntVector(0,0)
    };

    for(int i = 0; i < 8; i++)
    {
        IntVector index = pos + offset[i];
        if(board[index.x()][index.y()].type == CellType::Empty)
            return false;
        if(!IsInBounds((pos + offset[i]), IntVector(0,0)))
            return false;
    }
    return true;
}

void GenerateMaze::Generate()
{
    if(firstTime)
        Initialize();
    bool go = true;
    while(go)
    {
        if(pathCells.empty())
            break;

        if(board[checkCell.x()][checkCell.y()].directions.empty())
        {
            checkCell = pathCells.last();
            pathCells.removeLast();
            continue;
        }

        int direction = rand() % board[checkCell.x()][checkCell.y()].directions.count();
        IntVector index = checkCell + (board[checkCell.x()][checkCell.y()].directions[direction] * 2);

        if(!IsValid(index))
        {
            board[checkCell.x()][checkCell.y()].directions.removeAt(direction);
            continue;
        }

        board[index.x()][index.y()].type = CellType::Empty;

        if(checkCell.x() == index.x())
        {
            IntVector tempPos = IntVector(checkCell.x(), ((checkCell.y() + index.y()))/2);
            board[tempPos.x()][tempPos.y()].type = CellType::Empty;
        }
        if(checkCell.y() == index.y())
        {
            IntVector tempPos = IntVector((checkCell.x() + index.x())/2, checkCell.y());
            board[tempPos.x()][tempPos.y()].type = CellType::Empty;
        }

        checkCell = index;
        pathCells.push_back(checkCell);

        go=false;
    }
}
