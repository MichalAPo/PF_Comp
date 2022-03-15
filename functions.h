#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QColor>
#include <QPainter>
#include "structures.h"

class functions
{
public:

    functions();

    IntVector CalculateOnBoardPosition(IntVector, IntVector);
    IntVector CalculateWorldPosition(IntVector, IntVector);
    bool IsInBounds(IntVector, IntVector);
};

#endif // FUNCTIONS_H
