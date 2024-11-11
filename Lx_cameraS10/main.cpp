#include "Lx_cameraS10.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lx_cameraS10 w;
    w.show();
    return a.exec();
}
