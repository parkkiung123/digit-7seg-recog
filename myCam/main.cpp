#include "mycam.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyCam w;
    w.show();

    return a.exec();
}
