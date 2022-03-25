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

#include "astar.h"
#include "dfs.h"
#include "dijkstra.h"
#include "drawmanager.h"
#include "pathfindingbase.h"

class mainmanager: public QGraphicsView
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

    astar* aStarWindow;
    dfs* dfsWindow;
    dfs* bfsWindow;
    dijkstra* dijkstraWindow;
    drawmanager* drawManager;
};

#endif // MAINMANAGER_H
