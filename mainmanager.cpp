#include "mainmanager.h"

mainmanager::mainmanager(QWidget *parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene(0,0,screenWidth,screenHeight);
    setScene(scene);

    pix = new QPixmap(screenWidth,screenHeight);
    pix->fill(Qt::white);

    paint = new QPainter(pix);
    paint->setPen(QColor(0,0,0,255));
    paint->setBrush(QColor(255,255,255,255));

    test = new testwindow(QVector2D(25.0f,25.0f), 31, paint);
    test2 = new testwindow(QVector2D(360.0f,25.0f), 31, paint);
    test3 = new testwindow(QVector2D(695.0f,25.0f), 31, paint);

    astarPF = new astar(test);
    dfsPF = new dfs(test2);
    bfsPF = new dfs(test3);

    gen = new GenerateMaze(test);
    gen2 = new GenerateMaze(test2);
    gen3 = new GenerateMaze(test3);

    scene->addPixmap(*pix);
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
            test->ClearPath();
            test2->ClearPath();
            test3->ClearPath();

            astarPF->FindPath();
            dfsPF->FindPath('d');
            bfsPF->FindPath('b');

            astarPF->DrawVisited(astarPF->visitedCells);
            dfsPF->DrawVisited(dfsPF->visitedCells);
            bfsPF->DrawVisited(bfsPF->visitedCells);

            astarPF->DrawPath(astarPF->path);
            dfsPF->DrawPath(dfsPF->path);
            bfsPF->DrawPath(bfsPF->path);

            scene->addPixmap(*pix);
            break;
        }
        case Qt::Key_C:
        {
            test->ClearPath();
            test2->ClearPath();
            test3->ClearPath();

            scene->addPixmap(*pix);
            break;
        }
        case Qt::Key_G:
        {
            test->Clear();
            test2->Clear();
            test3->Clear();
            gen->Generate();
            gen2->maze = gen->maze;
            gen3->maze = gen->maze;
            gen2->DrawMaze();
            gen3->DrawMaze();
            scene->addPixmap(*pix);
            break;
        }

    }
}

void mainmanager::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        OneCell cellPos = OneCell(QVector2D(event->scenePosition().x(), event->scenePosition().y()), type);
        test->ChangeOneCell(cellPos, color);
        test2->ChangeOneCell(cellPos, color);
        test3->ChangeOneCell(cellPos, color);
        scene->addPixmap(*pix);
    }
}
