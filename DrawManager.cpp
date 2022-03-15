#include "DrawManager.h"

DrawManager::DrawManager(QPainter* paint)
{
    paintPointer = paint;
}

void DrawManager::DrawBoard(testwindow* window){
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            IntVector worldPos = CalculateWorldPosition(IntVector(i,j), window->boardPosition);
            paintPointer->drawRect(worldPos.x(),worldPos.y(),cellSize,cellSize);
        }
    }
}

void DrawManager::ClearPath(testwindow* window)
{
    paintPointer->setBrush(QColor(255,255,255,255));
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            if(window->board[i][j].type != CellType::Path || window->board[j][i].type != CellType::Visited)
                continue;
            IntVector worldPos = CalculateWorldPosition(IntVector(j,i), window->boardPosition);
            paintPointer->drawRect(worldPos.x(),worldPos.y(),cellSize,cellSize);
            window->ChangeType(IntVector(i,j), CellType::Empty);

        }
    }
}

void DrawManager::Clear(testwindow* window)
{
    window->startPos = IntVector(-1,-1);
    window->targetPos = IntVector(-1,-1);
    paintPointer->setBrush(QColor(255,255,255,255));
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            IntVector worldPos = CalculateWorldPosition(IntVector(i,j), window->boardPosition);
            paintPointer->drawRect(worldPos.x(),worldPos.y(),cellSize,cellSize);
            window->ChangeType(IntVector(i,j), CellType::Empty);
        }
    }
}

void DrawManager::ChangeOneCell(testwindow* window, IntVector cellPosition, QColor color, CellType type)
{
    IntVector boardPosition = window->boardPosition;
    if(!IsInBounds(cellPosition, boardPosition))
        return;

    paintPointer->setBrush(color);

    IntVector boardPos = CalculateOnBoardPosition(cellPosition, boardPosition);
    window->ChangeType(boardPos, type);

    IntVector cPos = CalculateWorldPosition(boardPos, boardPosition);
    paintPointer->drawRect(cPos.x(),cPos.y(),cellSize,cellSize);

    if(paintPointer->brush().color() == QColor(0,255,0,255))
    {
        if(IsInBounds(window->startPos, IntVector(0,0)))
        {
            paintPointer->setBrush(QColor(255,255,255,255));
            IntVector drawPos = CalculateWorldPosition(window->startPos, boardPosition);
            paintPointer->drawRect(drawPos.x(),drawPos.y(),cellSize,cellSize);
            window->ChangeType(drawPos, CellType::Empty);
        }
        window->startPos = boardPos;
        paintPointer->setBrush(QColor(0,255,0,255));
    }

    else if(paintPointer->brush().color() == QColor(255,0,0,255))
    {
        if(IsInBounds(window->targetPos, IntVector(0,0)))
        {
            paintPointer->setBrush(QColor(255,255,255,255));
            IntVector drawPos = CalculateWorldPosition(window->targetPos, boardPosition);
            paintPointer->drawRect(drawPos.x(),drawPos.y(),cellSize,cellSize);
            window->ChangeType(drawPos, CellType::Empty);
        }
        window->targetPos = boardPos;
        paintPointer->setBrush(QColor(255,0,0,255));
    }
}

void DrawManager::TypeText(IntVector pos, QString text)
{
    paintPointer->setFont(QFont("times",5));
    paintPointer->drawText(QRect(pos.x(), pos.y(), cellSize, cellSize), Qt::AlignCenter, text);
}

/*
void DrawManager::DrawPath(QList<IntVector> path)
{
    for(auto it = path.begin(); it !=path.end(); ++it)
    {
            IntVector currentCell = IntVector((it->x() * cellSize)+windowPointer->boardPosition.x(), (it->y() * cellSize)+windowPointer->boardPosition.y());
            ChangeOneCell(currentCell, QColor(0,80,200,255), CellType::Path);
            //windowPointer->TypeText(currentCell, QString::number(cells[QVector2D(it->x(),it->y())].parentPosition.x())+","+QString::number(cells[QVector2D(it->x(),it->y())].parentPosition.y()));
    }
}

void DrawManager::DrawVisited(QList<IntVector> visited)
{
    for(auto it = visited.begin(); it !=visited.end(); ++it)
    {
        IntVector currentCell = IntVector((it->x() * cellSize)+windowPointer->boardPosition.x(), (it->y() * cellSize)+windowPointer->boardPosition.y());
        ChangeOneCell(currentCell, QColor(255,200,180,255), CellType::Visited);
    }
}*/

void DrawManager::DrawMaze(testwindow* window, GenerateMaze* maze)
{
    for(int y=0; y<boardSize; y++)
    {
        for(int x=0; x<boardSize; x++)
        {
            IntVector calPos = CalculateWorldPosition(IntVector(x,y), window->boardPosition);
            if(maze->board[x][y].type == CellType::Wall)
            {
                ChangeOneCell(window, calPos, QColor(0,0,0,255), CellType::Wall);
                window->board[x][y].type = CellType::Wall;
            }
        }

    }
}
