#include "testwindow.h"

testwindow::testwindow(QVector2D pos, int size, QPainter* paint)
{
    boardSize = size;
    paintPointer = paint;
    boardPosition = pos;
    CreateBoard();
}

void testwindow::DrawBoard(){
    for(auto it = board.begin(); it !=board.end(); ++it)
    {
        QVector2D worldPos = CalculateWorldPosition(it->position, boardPosition);
        paintPointer->drawRect(worldPos.x(),worldPos.y(),cellSize,cellSize);
    }
}

void testwindow::CreateBoard()
{
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
                board[QVector2D(j,i)] = OneCell(QVector2D(j,i));
            }
        }
    DrawBoard();
}

void testwindow::ClearPath()
{
    paintPointer->setBrush(QColor(255,255,255,255));
    for(auto it = board.begin(); it !=board.end(); ++it)
    {
        if(it->type != CellType::Wall && it->type != CellType::Start && it->type != CellType::Goal)
        {
            QVector2D worldPos = CalculateWorldPosition(it->position, boardPosition);
            paintPointer->drawRect(worldPos.x(),worldPos.y(),cellSize,cellSize);
        }
    }
}

void testwindow::Clear()
{
    startPos = QVector2D(-1,-1);
    targetPos = QVector2D(-1,-1);
    paintPointer->setBrush(QColor(255,255,255,255));
    for(auto it = board.begin(); it !=board.end(); ++it)
    {
        it->type = CellType::Empty;
        QVector2D worldPos = CalculateWorldPosition(it->position, boardPosition);
        paintPointer->drawRect(worldPos.x(),worldPos.y(),cellSize,cellSize);
    }
}

void testwindow::ChangeOneCell(OneCell cellPar, QColor color)
{
    if(!IsInBounds(cellPar.position, boardPosition, boardPosition + QVector2D((boardSize*cellSize), (boardSize*cellSize))))
        return;

    paintPointer->setBrush(color);

    QVector2D boardPos = CalculateOnBoardPosition(cellPar.position, boardPosition);
    board[boardPos]=OneCell(boardPos, cellPar.type);

    QVector2D cPos = CalculateWorldPosition(boardPos, boardPosition);
    paintPointer->drawRect(cPos.x(),cPos.y(),cellSize,cellSize);

    if(paintPointer->brush().color() == QColor(0,255,0,255))
    {
        if(IsInBounds(startPos, QVector2D(0,0), QVector2D(boardSize, boardSize)))
        {
            paintPointer->setBrush(QColor(255,255,255,255));
            QVector2D drawPos = CalculateWorldPosition(startPos, boardPosition);
            paintPointer->drawRect(drawPos.x(),drawPos.y(),cellSize,cellSize);
        }
        startPos = board[boardPos].position;
        paintPointer->setBrush(QColor(0,255,0,255));
    }

    else if(paintPointer->brush().color() == QColor(255,0,0,255))
    {
        if(IsInBounds(targetPos, QVector2D(0,0), QVector2D(boardSize, boardSize)))
        {
            paintPointer->setBrush(QColor(255,255,255,255));
            QVector2D drawPos = CalculateWorldPosition(targetPos, boardPosition);
            paintPointer->drawRect(drawPos.x(),drawPos.y(),cellSize,cellSize);
        }
        targetPos = board[boardPos].position;
        paintPointer->setBrush(QColor(255,0,0,255));
    }
}

void testwindow::TypeText(QVector2D pos, QString text)
{
    paintPointer->setFont(QFont("times",5));
    paintPointer->drawText(QRect(pos.x(), pos.y(), cellSize, cellSize), Qt::AlignCenter, text);
}

