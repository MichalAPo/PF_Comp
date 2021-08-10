#include "mainmanager.h"

mainmanager::mainmanager(QWidget *parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene(0,0,1200,800);
    setScene(scene);

    pix = new QPixmap(1200,800);
    pix->fill(Qt::white);

    paint = new QPainter(pix);
    paint->setPen(QColor(0,0,0,255));
    paint->setBrush(QColor(255,255,255,255));

    test = new testwindow(QVector2D(50.0f,50.0f), 51, paint);        //tabela dynamiczna
    test2 = new testwindow(QVector2D(600.0f,50.0f), 51, paint);

    astarPF = new astar(test);
    dfsPF = new dfs(test2);

    gen = new GenerateMaze(test);
    gen2 = new GenerateMaze(test2);

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
            break;
        }
        case Qt::Key_Space:
        {
            test->clearPath();
            test2->clearPath();
            astarPF->findPath();
            dfsPF->FindPath('d');
            astarPF->drawVisited(astarPF->visitedCells);
            dfsPF->DrawVisited(dfsPF->visitedCells);
            astarPF->drawPath(astarPF->path);
            dfsPF->DrawPath(dfsPF->path);
            scene->addPixmap(*pix);
            break;
        }
        case Qt::Key_C:
        {
            test->clearPath();
            test2->clearPath();
            scene->addPixmap(*pix);
            break;
        }
        case Qt::Key_G:
        {
            test->clear();
            test2->clear();
            gen->Generate();
            gen2->maze = gen->maze;
            gen2->DrawMaze();
            scene->addPixmap(*pix);
            break;
        }

    }
}

void mainmanager::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << event->windowPos().x() << " "<< event->windowPos().y();
    if(event->buttons() == Qt::LeftButton)
    {
        OneCell cellPos = OneCell(QVector2D(event->scenePosition().x(), event->scenePosition().y()), type);
        test->changeOneCell(cellPos, color);
        test2->changeOneCell(cellPos, color);
        scene->addPixmap(*pix);
    }
}
