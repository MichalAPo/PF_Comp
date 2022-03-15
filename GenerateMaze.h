#ifndef GENERATEMAZE_H
#define GENERATEMAZE_H

#include "testwindow.h"
#include "functions.h"

class GenerateMaze: public functions
{

public:

    GenerateMaze(testwindow*);
    bool IsValid(IntVector);
    void Generate();
    void Initialize();
    void DrawMaze();
    bool firstTime = true;

    QList<IntVector> pathCells;
    IntVector checkCell;
    OneCell board[boardSize][boardSize];
    testwindow* windowPointer;
};

#endif // GENERATEMAZE_H
