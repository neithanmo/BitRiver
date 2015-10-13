#include "gstvideo.h"
#include "gstaudio.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gstvideo w;
    w.show();
    //x.show();
    return a.exec();
}
