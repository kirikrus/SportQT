#include "SportQT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SportQT w;
    w.show();
    return a.exec();
}
