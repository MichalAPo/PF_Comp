#include "mainwindow.h"
#include "mainmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainmanager* window = new mainmanager();
    window->show();

    return a.exec();
}
