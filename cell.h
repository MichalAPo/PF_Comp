#ifndef CELL_H
#define CELL_H
#include "structures.h"
#include<QBrush>
#include <QPen>
#include <QGraphicsRectItem>

class cell: public QGraphicsRectItem
{
public:
    cell(OneCell*);
};

#endif // CELL_H
