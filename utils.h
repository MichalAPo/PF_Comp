#ifndef UTILS_H
#define UTILS_H

#include <QColor>
#include <QPainter>
#include "structures.h"

namespace utils
{
    IntVector CalculateOnBoardPosition(IntVector, IntVector);
    IntVector CalculateWorldPosition(IntVector, IntVector);
    bool IsInBounds(IntVector, IntVector);
    bool VectorContains(std::list<IntVector>, IntVector);
    std::list<IntVector> RemoveVectorElement(std::list<IntVector>, IntVector);
};

#endif // UTILS_H
