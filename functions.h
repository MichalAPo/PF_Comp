#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QVector2D>
#include <QColor>
#include "structures.h"

class functions
{
public:
    functions();
    QVector2D CalculateOnBoardPosition(QVector2D pos, QVector2D boardPosition);
    QVector2D CalculateWorldPosition(QVector2D pos, QVector2D boardPosition);
    bool IsInBounds(QVector2D pos,QVector2D lowerBounds ,QVector2D upperBounds);
    int CalculateIndex(QVector2D pos, QVector2D boardPosition, int boardSize);
};

#endif // FUNCTIONS_H
