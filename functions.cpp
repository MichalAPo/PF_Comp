#include "functions.h"

functions::functions()
{

}

QVector2D functions::CalculateOnBoardPosition(QVector2D pos, QVector2D boardPosition)
{
    return QVector2D((floor(pos.x() - boardPosition.x())/cellSize),
                     (floor(pos.y() - boardPosition.y())/cellSize));
}

QVector2D functions::CalculateWorldPosition(QVector2D pos, QVector2D boardPosition)
{
    return QVector2D((pos.x() * cellSize) + boardPosition.x(),
                     (pos.y() * cellSize) + boardPosition.y());
}

int functions::CalculateIndex(QVector2D pos, QVector2D boardPosition, int boardSize)
{
    QVector2D position = CalculateOnBoardPosition(pos, boardPosition);
    return (position.x()) + (floor(position.y())*boardSize);
}

bool functions::IsInBounds(QVector2D pos,QVector2D lowerBounds ,QVector2D upperBounds)
{
    return pos.x() >= lowerBounds.x()
            && pos.x() <= upperBounds.x()
            && pos.y() >= lowerBounds.y()
            && pos.y() <= upperBounds.y();
}
