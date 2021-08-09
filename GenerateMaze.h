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
    void Generate();
    void Initialize();
    void DrawMaze();

    QList<QVector2D> pathCells;
    QVector2D checkCell;
    QMap<QVector2D, OneCell> maze;
    testwindow* windowPointer;
};

#endif // GENERATEMAZE_H
