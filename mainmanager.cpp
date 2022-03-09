#include "mainmanager.h"

mainmanager::mainmanager(QWidget *parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene(0,0,screenWidth,screenHeight);
    setScene(scene);

    pixMap = new QPixmap(screenWidth,screenHeight);
    pixMap->fill(Qt::white);

    paint = new QPainter(pixMap);
    paint->setPen(QColor(0,0,0,255));
    paint->setBrush(QColor(255,255,255,255));

    aStarWindow = new testwindow(QVector2D(25.0f,25.0f), 31, paint);
    dfsWindow = new testwindow(QVector2D(360.0f,25.0f), 31, paint);
    bfsWindow = new testwindow(QVector2D(695.0f,25.0f), 31, paint);

    astarPF = new astar(aStarWindow);
    dfsPF = new dfs(dfsWindow);
    bfsPF = new dfs(bfsWindow);

    generateMazeAStar = new GenerateMaze(aStarWindow);
    generateMazeDFS = new GenerateMaze(dfsWindow);
    generateMazeBFS = new GenerateMaze(bfsWindow);

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
            type = CellType::Goal;
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
            bfsPF->ReconstructPath();
            break;
        }
        case Qt::Key_Space:
        {
            aStarWindow->ClearPath();
            dfsWindow->ClearPath();
            bfsWindow->ClearPath();

            astarPF->FindPath();
            dfsPF->FindPath(true);
            bfsPF->FindPath(false);

            astarPF->DrawVisited(astarPF->visitedCells);
            dfsPF->DrawVisited(dfsPF->visitedCells);
            bfsPF->DrawVisited(bfsPF->visitedCells);

            astarPF->DrawPath(astarPF->path);
            dfsPF->DrawPath(dfsPF->path);
            bfsPF->DrawPath(bfsPF->path);

            scene->addPixmap(*pixMap);
            break;
        }
        case Qt::Key_C:
        {
            aStarWindow->ClearPath();
            dfsWindow->ClearPath();
            bfsWindow->ClearPath();

            scene->addPixmap(*pixMap);
            break;
        }
        case Qt::Key_G:
        {
            aStarWindow->Clear();
            dfsWindow->Clear();
            bfsWindow->Clear();
            generateMazeAStar->Generate();
            generateMazeDFS->maze = generateMazeAStar->maze;
            generateMazeBFS->maze = generateMazeAStar->maze;
            generateMazeDFS->DrawMaze();
            generateMazeBFS->DrawMaze();
            scene->addPixmap(*pixMap);
            break;
        }

    }
}

void mainmanager::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        QVector2D mousePosition = QVector2D(event->scenePosition().x(), event->scenePosition().y());
        //OneCell cellPos = OneCell(QVector2D(event->scenePosition().x(), event->scenePosition().y()), type);
        aStarWindow->ChangeOneCell(mousePosition, color, type);
        dfsWindow->ChangeOneCell(mousePosition, color, type);
        bfsWindow->ChangeOneCell(mousePosition, color, type);
        scene->addPixmap(*pixMap);
    }
}
