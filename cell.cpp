#include "cell.h"

cell::cell(OneCell* cellPar)
{
    QColor color = QColor();
    color = QColor::fromRgb(255,255,255);
    setRect(cellPar->x, cellPar->y, cellSize, cellSize);

    switch (cellPar->type) {
        case Start:
        {
            color = QColor::fromRgb(0,255,0);
            break;
        }
        case Goal:
        {
            color = QColor::fromRgb(255,0,0);
            break;
        }
        case Check:
        {
            color = QColor::fromRgb(126,126,126);
            break;
        }
        case Wall:
        {
            color = QColor::fromRgb(0,0,0);
            break;
        }
        case Empty:
        {
            color = QColor::fromRgb(255,255,255);
            break;
        }
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush);

    QPen pen;
        pen.setWidth(1);
        pen.setColor(QColor::fromRgb(0,0,0,255));
        setPen(pen);


}
