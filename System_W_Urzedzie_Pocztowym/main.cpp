#include "mainwindow.h"
#include "database.h"
#include <QApplication>

int Database::lastID = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
 //   w.setGeometry(100, 100, 1100, 700);
    w.setWindowTitle("System w urzędzie pocztowym");
    w.show();
    return a.exec();
}
