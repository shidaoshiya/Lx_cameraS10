#include "Lx_s10_time.h"
#include <QtWidgets/QApplication>
#include <thread>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lx_s10_time w;
    
   //std::thread myThread(std::bind(&Lx_s10_time::SaveImage,&w,1));

    w.show();
    std::thread myThread([&w]() { w.SaveImage(); });
    return a.exec();
}
