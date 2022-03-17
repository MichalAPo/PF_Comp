#include "mainmanager.h"

mainmanager::mainmanager(QWidget *parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene(0,0,screenWidth,screenHeight);
    setScene(scene);

    pixMap = new QPixmap(screenWidth,screenHeight);
    pixMap->fill(Qt::white);

    paint = new QPainter(pixMap);
    paint->setPen(Qt::NoPen);
    //paint->setPen(QColor(0,0,0,255));
    paint->setBrush(QColor(255,255,255,255));

    aStarWindow = new astar(IntVector(25,25));
    dfsWindow = new dfs(IntVector(360,25));
    bfsWindow = new dfs(IntVector(695,25));

    drawManager = new drawmanager(paint);
    drawManager->DrawBoard(aStarWindow);
    drawManager->DrawBoard(dfsWindow);
    drawManager->DrawBoard(bfsWindow);

    scene->addPixmap(*pixMap);
}

void mainmanager::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_1:
        {
            //Start
            type = CellType::Start;
            color = QColor(0,255,0,255);
            break;
        }
        case Qt::Key_2:
        {
            //Goal
            type = CellType::Target;
            color = QColor(255,0,0,255);
            break;
        }
        case Qt::Key_3:
        {
            //Wall
            type = CellType::Wall;
            color = QColor(0,0,0,255);
            break;
        }
        case Qt::Key_4:
        {
            //Empty
            type = CellType::Empty;
            color = QColor(255,255,255,255);
            break;
        }
        case Qt::Key_Space:
        {
            drawManager->ClearPath(aStarWindow);
            drawManager->ClearPath(dfsWindow);
            drawManager->ClearPath(bfsWindow);

            aStarWindow->FindPath();
            dfsWindow->FindPath(true);
            bfsWindow->FindPath(false);

            drawManager->DrawVisited(aStarWindow);
            drawManager->DrawVisited(dfsWindow);
            drawManager->DrawVisited(bfsWindow);

            drawManager->DrawPath(aStarWindow);
            drawManager->DrawPath(dfsWindow);
            drawManager->DrawPath(bfsWindow);

            //drawManager->DrawTags(dfsWindow);

            scene->addPixmap(*pixMap);
            break;
        }
        case Qt::Key_C:
        {
            drawManager->ClearPath(aStarWindow);
            drawManager->ClearPath(dfsWindow);
            drawManager->ClearPath(bfsWindow);
            scene->addPixmap(*pixMap);
            break;
        }
        case Qt::Key_G:
        {
            drawManager->Clear(aStarWindow);
            drawManager->Clear(dfsWindow);
            drawManager->Clear(bfsWindow);
            aStarWindow->GenerateMaze();
            drawManager->DrawMaze(aStarWindow, aStarWindow);
            drawManager->DrawMaze(dfsWindow, aStarWindow);
            drawManager->DrawMaze(bfsWindow, aStarWindow);
            scene->addPixmap(*pixMap);
            break;
        }

    }
}

void mainmanager::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        IntVector mousePosition = IntVector(event->scenePosition().x(), event->scenePosition().y());
        drawManager->ChangeOneCell(aStarWindow, mousePosition, color, type);
        drawManager->ChangeOneCell(dfsWindow ,mousePosition, color, type);
        drawManager->ChangeOneCell(bfsWindow ,mousePosition, color, type);
        scene->addPixmap(*pixMap);
    }
}
