#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include "structures.h"
#include "cell.h"
#include "functions.h"

class testwindow: public QGraphicsRectItem, public functions
{
public:
    testwindow(IntVector);
    void CreateBoard(); 

    IntVector boardPosition;
    OneCell board[boardSize][boardSize];
    IntVector startPos = IntVector(-1,-1);
    IntVector targetPos = IntVector(-1,-1);
    void ChangeType(IntVector, CellType);
};

#endif // TESTWINDOW_Hs
