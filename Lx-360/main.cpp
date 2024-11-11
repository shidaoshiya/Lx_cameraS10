#include "Lx360.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lx360 w;
    w.show();
    return a.exec();
}
