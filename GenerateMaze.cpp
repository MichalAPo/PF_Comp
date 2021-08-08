#include "GenerateMaze.h"

GenerateMaze::GenerateMaze(testwindow* window)
{
    windowPointer = window;
    generating = true;
}

void GenerateMaze::Initialize()
{
    for(int y=0; y<windowPointer->boardSize; y++)
    {
        for(int x=0; x<windowPointer->boardSize; x++)
        {
            maze[QVector2D(x,y)] = OneCell(QVector2D(x,y), CellType::Wall);
        }
    }

    QVector2D randomCell = QVector2D(rand() % windowPointer->boardSize, rand() % windowPointer->boardSize);
    while(!IsValid(randomCell))
    {
        randomCell = QVector2D(rand() % windowPointer->boardSize, rand() % windowPointer->boardSize);
    }

    maze[randomCell].type = CellType::Empty;
    maze[randomCell].parentPosition = QVector2D(-1,-1);
    checkCell = randomCell;
}

bool GenerateMaze::IsValid(QVector2D startCell)
{
    QVector2D offset[8]=
    {
        QVector2D(1,1),
        QVector2D(0,1),
        QVector2D(1,0),
        QVector2D(-1,-1),
        QVector2D(-1,1),
        QVector2D(1,-1),
        QVector2D(-1,0),
        QVector2D(0,-1)
    };

    for(int i = 0; i < 8; i++)
    {
        if(maze[startCell + offset[i]].type == CellType::Empty && (startCell + offset[i]) != maze[startCell].parentPosition
                && (startCell + offset[i]) != maze[maze[startCell].parentPosition].parentPosition)
            return false;
        if(!IsInBounds((startCell + offset[i]), QVector2D(0,0), QVector2D(windowPointer->boardSize -1, windowPointer->boardSize -1)))
            return false;
    }
    return true;
}

void GenerateMaze::Generate()
{
    if(generating)
    Initialize();

    generating = true;

    while(generating)
    {
        if(checkCell == QVector2D(-1,-1))
            break;

        if(maze[checkCell].directions.empty())
        {
            maze[checkCell].visited = true;
            checkCell = maze[checkCell].parentPosition;
            generating = false;
            continue;
        }

        int direction = rand() % maze[checkCell].directions.count();

        if(maze[checkCell + maze[checkCell].directions[direction]].parentPosition == QVector2D(-2,-2))
            maze[checkCell + maze[checkCell].directions[direction]].parentPosition = checkCell;

        if(!IsValid(checkCell + maze[checkCell].directions[direction]))
        {
            maze[checkCell].directions.removeAt(direction);
            generating = false;
            continue;
        }

        //maze[checkCell].directions.removeAt(maze[checkCell].directions.indexOf(-maze[checkCell].directions[direction]));
        maze[checkCell + maze[checkCell].directions[direction]].type = CellType::Empty;
        checkCell = checkCell + maze[checkCell].directions[direction];
        generating = false;
    }
    DrawMaze();
    windowPointer->changeOneCell(OneCell(CalculateWorldPosition(checkCell, windowPointer->boardPosition)
                                         ,CellType::Wall), QColor(0,255,0,255));
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

/*QVector4D rCell = QVector4D(rand() % windowPointer->boardSize, rand() % windowPointer->boardSize, 0, 0);
    board[rCell.toVector2D()] = false;
    cellsToCheck = GenerateCelsToCheck(rCell.toVector2D());
    while(!cellsToCheck.isEmpty())
    {
       QVector4D currentCell = cellsToCheck[rand()%(cellsToCheck.count())];

       cellsToCheck.remove(cellsToCheck.indexOf(currentCell));
       cellsToCheck = cellsToCheck + GenerateCelsToCheck(currentCell.toVector2D());
       board[currentCell.toVector2D()]=false;
       if(currentCell.x() == currentCell.z())
       {
          QVector2D mid = QVector2D(currentCell.x(), (currentCell.w()-currentCell.y())/2);
          board[QVector2D(mid.x(), currentCell.y()+mid.y())]=false;
       }
       else if(currentCell.y() == currentCell.w())
       {
           QVector2D mid = QVector2D((currentCell.z()-currentCell.x())/2, currentCell.y());
           board[QVector2D(currentCell.x()+mid.x(), mid.y())]=false;

       }


       rCell = currentCell;
    }*/

