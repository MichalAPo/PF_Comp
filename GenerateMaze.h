#ifndef GENERATEMAZE_H
#define GENERATEMAZE_H
#include "testwindow.h"
#include "structures.h"
#include "functions.h"

class GenerateMaze: public functions
{

public:

    GenerateMaze(testwindow*);
    bool IsValid(QVector2D);

    bool generating;
    QVector2D checkCell;
    bool backtracking;
    QMap<QVector2D, OneCell> maze;
    testwindow* windowPointer;
    void Generate();
    void Initialize();
    void DrawMaze();
};

#endif // GENERATEMAZE_H
