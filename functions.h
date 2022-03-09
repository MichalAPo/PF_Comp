#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QVector2D>
#include <QColor>
#include <QPainter>
#include "structures.h"

class functions
{
public:

    functions();

    QVector2D CalculateOnBoardPosition(QVector2D, QVector2D);
    QVector2D CalculateWorldPosition(QVector2D, QVector2D);
    bool IsInBounds(QVector2D, QVector2D, QVector2D);
};

#endif // FUNCTIONS_H
