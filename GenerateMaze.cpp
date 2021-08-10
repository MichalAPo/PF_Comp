#include "GenerateMaze.h"
#include <QMap>

GenerateMaze::GenerateMaze(testwindow* window)
{
    windowPointer = window;
    //Initialize();
}

void GenerateMaze::Initialize()
{
    pathCells = QList<QVector2D>();

    for(int y=0; y<windowPointer->boardSize; y++)
    {
        for(int x=0; x<windowPointer->boardSize; x++)
        {
            maze[QVector2D(x,y)] = OneCell(QVector2D(x,y), CellType::Wall);
        }
    }

    QVector2D firtsCell = QVector2D(1, 1);

    maze[firtsCell].type = CellType::Empty;
    checkCell = firtsCell;
    pathCells.push_back(checkCell);
}

bool GenerateMaze::IsValid(QVector2D pos)
{
    QVector2D offset[9] =
    {
        QVector2D(1,0),
        QVector2D(0,1),
        QVector2D(0,-1),
        QVector2D(1,-1),
        QVector2D(1,1),
        QVector2D(-1,-1),
        QVector2D(-1,1),
        QVector2D(-1,0),
        QVector2D(0,0)
    };

    for(int i = 0; i < 8; i++)
    {
        if(maze[pos + offset[i]].type == CellType::Empty)
            return false;
        if(!IsInBounds((pos + offset[i]), QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1)))
            return false;
    }
    return true;
}

void GenerateMaze::Generate()
{
    Initialize();
    //bool a = true;

    while(true)
    {
        if(pathCells.empty())
            break;

        if(maze[checkCell].directions.empty())
        {
            checkCell = pathCells.last();
            pathCells.removeLast();
            continue;
        }

        int direction = rand() % maze[checkCell].directions.count();

        if(!IsValid(checkCell + (maze[checkCell].directions[direction]) * 2))
        {
            maze[checkCell].directions.removeAt(direction);
            continue;
        }

        maze[checkCell + (maze[checkCell].directions[direction] * 2)].type = CellType::Empty;

        if(checkCell.x() == (checkCell.x() + (maze[checkCell].directions[direction].x() * 2)))
        {
            QVector2D tempPos = QVector2D(checkCell.x(), ((checkCell.y() + (checkCell.y() + (maze[checkCell].directions[direction].y() * 2))))/2);
            maze[tempPos].type = CellType::Empty;
        }
        if(checkCell.y() == (checkCell.y() + (maze[checkCell].directions[direction].y() * 2)))
        {
            QVector2D tempPos = QVector2D((checkCell.x() + (checkCell.x() + (maze[checkCell].directions[direction].x() * 2)))/2, checkCell.y());
            maze[tempPos].type = CellType::Empty;
        }

        checkCell = checkCell + (maze[checkCell].directions[direction] * 2);
        pathCells.push_back(checkCell);
        //a = false;
    }
    DrawMaze();
    //maze.clear();
}

void GenerateMaze::DrawMaze()
{
    for(int y=0; y<windowPointer->boardSize; y++)
    {
        for(int x=0; x<windowPointer->boardSize; x++)
        {
            QVector2D pos = QVector2D(x,y);
            QVector2D calPos = CalculateWorldPosition(pos, windowPointer->boardPosition);
            if(maze[pos].type == CellType::Wall)
            {
                windowPointer->changeOneCell(OneCell(calPos,CellType::Wall), QColor(0,0,0,255));
            }
        }

    }
}
