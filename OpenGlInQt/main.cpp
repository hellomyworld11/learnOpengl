#include "HelloOpenGl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HelloOpenGl w;
    w.show();
    return a.exec();
}
