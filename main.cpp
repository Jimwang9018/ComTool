#include "comtool.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ComTool w;
    w.resize(800, 555);
    w.show();
    return a.exec();
}
