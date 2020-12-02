#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    APPLICATION_DIR = QCoreApplication::applicationDirPath();
    qDebug() << "APPLICATION_DIR:" << APPLICATION_DIR;

    MainWindow w;
    w.show();

    return a.exec();
}
