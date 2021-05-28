#include <QApplication>

#include "EarthWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EarthWidget w;
    w.show();
    return a.exec();
}
