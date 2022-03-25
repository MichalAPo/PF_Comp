#include "drawmanager.h"

using namespace utils;

drawmanager::drawmanager(QPainter* paint)
{
    paintPointer = paint;
}

void drawmanager::DrawBoard(pathfindingbase* window, QString name){
    //paintPointer->setBrush(QColor(0,0,0,255));
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            int colorModif = window->board[i][j].travelCost/2;
            paintPointer->setBrush(QColor(0,0,0,0 + colorModif));
            IntVector worldPos = CalculateWorldPosition(IntVector(i,j), window->boardPosition);
            paintPointer->drawRect(worldPos.x,worldPos.y,cellSize,cellSize);
        }
    }
    QPen pen;
    pen.setWidth(cellSize); pen.setJoinStyle(Qt::MiterJoin);
    paintPointer->setPen(pen);
    paintPointer->drawRect((float)window->boardPosition.x-((float)cellSize/2),(float)window->boardPosition.y-((float)cellSize/2),
                           (boardSize*cellSize)+cellSize,(boardSize*cellSize)+cellSize);
    QRect br;
    paintPointer->drawText(QRect(window->boardPosition.x,window->boardPosition.y-spaceBetween+5, cellSize * boardSize, spaceBetween), 0, name,  &br);
    paintPointer->setPen(Qt::NoPen);
}

void drawmanager::DrawTags(pathfindingbase* window){
    paintPointer->setBrush(QColor(0,0,0,255));
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            IntVector position = CalculateWorldPosition(IntVector(j,i), window->boardPosition);
            switch(window->board[j][i].type){
                case CellType::Check:
                TypeText(position, "C");
                break;
                case CellType::Empty:
                TypeText(position, "E");
                break;
                case CellType::Target:
                TypeText(position, "T");
                break;
                case CellType::Path:
                TypeText(position, "P");
                break;
                case CellType::Start:
                TypeText(position, "S");
                break;
                case CellType::Visited:
                TypeText(position, "V");
                break;
                case CellType::Wall:
                TypeText(position, "W");
                break;
            }
        }
    }
}

void drawmanager::ClearPath(pathfindingbase* window)
{
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            if(window->board[j][i].type != CellType::Path && window->board[j][i].type != CellType::Visited)
                continue;
            IntVector worldPos = IntVector((j * cellSize)+window->boardPosition.x, (i * cellSize)+window->boardPosition.y);
            ChangeOneCell(window, worldPos, QColor(255,255,255,255), CellType::Empty);
        }
    }
}

void drawmanager::Clear(pathfindingbase* window)
{
    window->startPos = IntVector(-1,-1);
    window->targetPos = IntVector(-1,-1);
    paintPointer->setBrush(QColor(255,255,255,255));
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            IntVector worldPos = CalculateWorldPosition(IntVector(i,j), window->boardPosition);
            ChangeOneCell(window, worldPos, QColor(255,255,255,255), CellType::Empty);
        }
    }
}

void drawmanager::ChangeOneCell(pathfindingbase* window, IntVector cellPosition, QColor color, CellType type)
{
    IntVector boardPosition = window->boardPosition;
    if(!IsInBounds(cellPosition, boardPosition))
        return;

    paintPointer->setBrush(color);

    IntVector boardPos = CalculateOnBoardPosition(cellPosition, boardPosition);
    window->board[boardPos.x][boardPos.y].ChangeCell(type);// = OneCell(type);

    if(!IsInBounds(boardPos, IntVector(0,0)))
        return;

    IntVector cPos = CalculateWorldPosition(boardPos, boardPosition);
    paintPointer->drawRect(cPos.x,cPos.y,cellSize,cellSize);

    if(paintPointer->brush().color() == QColor(0,255,0,255))
    {
        if(IsInBounds(window->startPos, IntVector(0,0)) && boardPos != window->startPos)
        {
            paintPointer->setBrush(QColor(255,255,255,255));
            IntVector drawPos = CalculateWorldPosition(window->startPos, boardPosition);
            paintPointer->drawRect(drawPos.x,drawPos.y,cellSize,cellSize);
            window->board[window->startPos.x][window->startPos.y].ChangeCell(CellType::Empty);// = OneCell(CellType::Empty);
        }
        window->startPos = boardPos;
        paintPointer->setBrush(QColor(0,255,0,255));
    }

    else if(paintPointer->brush().color() == QColor(255,0,0,255))
    {
        if(IsInBounds(window->targetPos, IntVector(0,0)) && boardPos != window->targetPos)
        {
            paintPointer->setBrush(QColor(255,255,255,255));
            IntVector drawPos = CalculateWorldPosition(window->targetPos, boardPosition);
            paintPointer->drawRect(drawPos.x,drawPos.y,cellSize,cellSize);
            window->board[window->targetPos.x][window->targetPos.y].ChangeCell(CellType::Empty);// = OneCell(CellType::Empty);
        }
        window->targetPos = boardPos;
        paintPointer->setBrush(QColor(255,0,0,255));
    }
}

void drawmanager::TypeText(IntVector pos, QString text)
{
    paintPointer->setFont(QFont("times",5));
    paintPointer->drawText(QRect(pos.x, pos.y, cellSize, cellSize), Qt::AlignCenter, text);
}


void drawmanager::DrawPath(pathfindingbase* window)
{
    for(auto it = window->path.begin(); it !=window->path.end(); ++it)
    {
        IntVector currentCell = IntVector((it->x * cellSize)+window->boardPosition.x, (it->y * cellSize)+window->boardPosition.y);
        ChangeOneCell(window, currentCell, QColor(0,80,200,255), CellType::Path);
    }
}

void drawmanager::DrawVisited(pathfindingbase* window)
{
    for(auto it = window->visitedCells.begin(); it != window->visitedCells.end(); ++it)
    {
        IntVector currentCell = IntVector((it->x * cellSize)+window->boardPosition.x, (it->y * cellSize)+window->boardPosition.y);
        ChangeOneCell(window, currentCell, QColor(255,200,180,80), CellType::Visited);
    }
}

void drawmanager::DrawMaze(pathfindingbase* window, pathfindingbase* maze)
{
    for(int y=0; y<boardSize; y++)
    {
        for(int x=0; x<boardSize; x++)
        {
            IntVector calPos = CalculateWorldPosition(IntVector(x,y), window->boardPosition);
            if(maze->maze[x][y].type == CellType::Wall)
                ChangeOneCell(window, calPos, QColor(0,0,0,255), CellType::Wall);
                //window->board[x][y].ChangeCell(CellType::Wall);// = OneCell(CellType::Wall);
        }

    }
}
