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

    int seed = rand();
    aStarWindow = new astar(IntVector(spaceBetween,spaceBetween), seed);
    dfsWindow = new dfs(IntVector((3*spaceBetween)+(cellSize*boardSize),spaceBetween), seed);
    bfsWindow = new dfs(IntVector((3*spaceBetween)+(cellSize*boardSize),(3*spaceBetween)+(cellSize*boardSize)), seed);
    dijkstraWindow = new dijkstra(IntVector(spaceBetween,(3*spaceBetween)+(cellSize*boardSize)), seed);

    drawManager = new drawmanager(paint);
    drawManager->DrawBoard(aStarWindow, "AStar");
    drawManager->DrawBoard(dfsWindow, "DFS");
    drawManager->DrawBoard(bfsWindow, "BFS");
    drawManager->DrawBoard(dijkstraWindow, "Dijkstra");

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
            drawManager->ClearPath(dijkstraWindow);

            aStarWindow->FindPath();
            dfsWindow->FindPath(true);
            bfsWindow->FindPath(false);
            dijkstraWindow->FindPath();

            drawManager->DrawVisited(aStarWindow);
            drawManager->DrawVisited(dfsWindow);
            drawManager->DrawVisited(bfsWindow);
            drawManager->DrawVisited(dijkstraWindow);

            drawManager->DrawPath(aStarWindow);
            drawManager->DrawPath(dfsWindow);
            drawManager->DrawPath(bfsWindow);
            drawManager->DrawPath(dijkstraWindow);

            //drawManager->DrawTags(dfsWindow);

            scene->addPixmap(*pixMap);
            break;
        }
        case Qt::Key_C:
        {
            drawManager->ClearPath(aStarWindow);
            drawManager->ClearPath(dfsWindow);
            drawManager->ClearPath(bfsWindow);
            drawManager->ClearPath(dijkstraWindow);
            scene->addPixmap(*pixMap);
            break;
        }
        case Qt::Key_G:
        {
            drawManager->Clear(aStarWindow);
            drawManager->Clear(dfsWindow);
            drawManager->Clear(bfsWindow);
            drawManager->Clear(dijkstraWindow);

            aStarWindow->GenerateMaze();
            drawManager->DrawMaze(aStarWindow, aStarWindow);
            drawManager->DrawMaze(dfsWindow, aStarWindow);
            drawManager->DrawMaze(bfsWindow, aStarWindow);
            drawManager->DrawMaze(dijkstraWindow, aStarWindow);
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
        drawManager->ChangeOneCell(dfsWindow ,mousePosition + dfsWindow->boardPosition - IntVector(spaceBetween,spaceBetween), color, type);
        drawManager->ChangeOneCell(bfsWindow ,mousePosition + bfsWindow->boardPosition - IntVector(spaceBetween,spaceBetween), color, type);
        drawManager->ChangeOneCell(dijkstraWindow ,mousePosition + dijkstraWindow->boardPosition - IntVector(spaceBetween,spaceBetween), color, type);
        scene->addPixmap(*pixMap);
    }
}


