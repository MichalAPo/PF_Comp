#include "pathfindingbase.h"

using namespace utils;

pathfindingbase::pathfindingbase(IntVector pos, int seed)
{
    boardPosition=pos;
    CreateBoard(seed);
}

void pathfindingbase::CreateBoard(int seed)
{
    srand(seed);
    for(int i=0; i<boardSize; i++)
    {
        for(int j=0; j<boardSize; j++)
        {
            board[i][j] = OneCell();
            board[i][j].travelCost = rand() % 255 + 1;
        }
    }
}

void pathfindingbase::Initialize()
{
    path.clear();
    visitedCells.clear();
    checkedCells.clear();
    board[startPos.x][startPos.y].visited = false;
    board[targetPos.x][targetPos.y].visited = false;
}

std::list<IntVector> pathfindingbase::ReconstructPath()
{
    std::list<IntVector> path = std::list<IntVector>();
    IntVector pos = board[targetPos.x][targetPos.y].parentPosition;
    path.push_back(pos);

    while(pos != startPos)
    {
        pos = board[pos.x][pos.y].parentPosition;

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
        if(maze[index.x][index.y].type == CellType::Empty)
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
    currentCell = IntVector(1,1);
    mazePaths.push_back(currentCell);

    while(true)
    {
        if(mazePaths.empty())
            break;

        if(maze[currentCell.x][currentCell.y].directions.empty())
        {
            currentCell = mazePaths.back();
            mazePaths.pop_back();
            continue;
        }

        int direction = rand() % maze[currentCell.x][currentCell.y].directions.size();
        IntVector index = currentCell + (maze[currentCell.x][currentCell.y].directions[direction] * 2);

        if(!IsValid(index))
        {
            maze[currentCell.x][currentCell.y].directions.erase(maze[currentCell.x][currentCell.y].directions.begin()+direction);
            continue;
        }

        maze[index.x][index.y].type = CellType::Empty;

        if(currentCell.x == index.x)
        {
            IntVector tempPos = IntVector(currentCell.x, ((currentCell.y + index.y))/2);
            maze[tempPos.x][tempPos.y].type = CellType::Empty;
        }
        if(currentCell.y == index.y)
        {
            IntVector tempPos = IntVector((currentCell.x + index.x)/2, currentCell.y);
            maze[tempPos.x][tempPos.y].type = CellType::Empty;
        }

        currentCell = index;
        mazePaths.push_back(currentCell);
    }
}

std::list<IntVector> pathfindingbase::GetNeighbours(IntVector position)
{
    std::list<IntVector> neighbours;

    for(int i=0; i<4; i++)
    {
        std::vector<IntVector> a = board[position.x][position.y].directions;
        IntVector p = position + board[position.x][position.y].directions[i];
        if (!IsInBounds(p, IntVector(0,0)))
            continue;
        if(board[p.x][p.y].visited)
            continue;
        if(board[p.x][p.y].type != CellType::Wall)
            neighbours.push_back(p);
//       board[p.x][p.y].visited=true;
    }
    return neighbours;
}
