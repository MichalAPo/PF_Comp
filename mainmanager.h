#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QBrush>
#include <QPen>
#include "testwindow.h"
#include "structures.h"
#include "astar.h"
#include "GenerateMaze.h"

class mainmanager: public QGraphicsView
{
public:
    mainmanager(QWidget *parent=NULL);
    void mousePressEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void addToScene();
    QGraphicsScene* scene;
    QPixmap *pix;
    QColor color = QColor(255,255,255,255);
    QPainter *paint;
    CellType type = CellType::Empty;
    testwindow* test;
    testwindow* test2;
    astar* astar1;
    astar* astar2;
    GenerateMaze* gen;
    GenerateMaze* gen2;
};

#endif // MAINMANAGER_H
