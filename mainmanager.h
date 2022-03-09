#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QBrush>
#include <QPen>
#include <QScreen>
#include <QGuiApplication>
#include <QBitmap>
#include "testwindow.h"
#include "structures.h"
#include "astar.h"
#include "GenerateMaze.h"
#include "dfs.h"


class mainmanager: public QGraphicsView, public functions
{
public:
    mainmanager(QWidget *parent=NULL);
    void mousePressEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void AddToScene();

    QGraphicsScene* scene;
    QPixmap* pixMap;
    QColor color = QColor(255,255,255,255);
    QPainter *paint;
    CellType type = CellType::Empty;
    testwindow* aStarWindow;
    testwindow* dfsWindow;
    testwindow* bfsWindow;
    astar* astarPF;
    dfs* dfsPF;
    dfs* bfsPF;
    GenerateMaze* generateMazeAStar;
    GenerateMaze* generateMazeDFS;
    GenerateMaze* generateMazeBFS;
};

#endif // MAINMANAGER_H
