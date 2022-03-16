#include "pathfindingbase.h"

using namespace utils;

pathfindingbase::pathfindingbase(IntVector pos)
{
    boardPosition=pos;
    CreateBoard();
}

void pathfindingbase::CreateBoard()
{
    for(int i=0; i<boardSize; i++)
    {
        for(int j=0; j<boardSize; j++)
        {
            board[i][j] = OneCell();
        }
    }
}

void pathfindingbase::Initialize()
{
    path.clear();
    visitedCells.clear();
    checkedCells.clear();
}

QList<IntVector> pathfindingbase::ReconstructPath()
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

bool pathfindingbase::IsValid(IntVector pos)
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
        if(maze[index.x()][index.y()].type == CellType::Empty)
            return false;
        if(!IsInBounds((pos + offset[i]), IntVector(0,0)))
            return false;
    }
    return true;
}

void pathfindingbase::GenerateMaze()
{
    for(int y = 0; y<boardSize; y++)
    {
        for(int x = 0; x<boardSize; x++)
        {
            maze[x][y] = OneCell(CellType::Wall);
        }
    }


    maze[1][1].type = CellType::Empty;
    checkCell = IntVector(1,1);
    mazePaths.push_back(checkCell);

    while(true)
    {
        if(mazePaths.empty())
            break;

        if(maze[checkCell.x()][checkCell.y()].directions.empty())
        {
            checkCell = mazePaths.last();
            mazePaths.removeLast();
            continue;
        }

        int direction = rand() % maze[checkCell.x()][checkCell.y()].directions.count();
        IntVector index = checkCell + (maze[checkCell.x()][checkCell.y()].directions[direction] * 2);

        if(!IsValid(index))
        {
            maze[checkCell.x()][checkCell.y()].directions.removeAt(direction);
            continue;
        }

        maze[index.x()][index.y()].type = CellType::Empty;

        if(checkCell.x() == index.x())
        {
            IntVector tempPos = IntVector(checkCell.x(), ((checkCell.y() + index.y()))/2);
            maze[tempPos.x()][tempPos.y()].type = CellType::Empty;
        }
        if(checkCell.y() == index.y())
        {
            IntVector tempPos = IntVector((checkCell.x() + index.x())/2, checkCell.y());
            maze[tempPos.x()][tempPos.y()].type = CellType::Empty;
        }

        checkCell = index;
        mazePaths.push_back(checkCell);
    }
}
