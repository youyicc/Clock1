#include "Clock1.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Clock1 mainWidget;
    mainWidget.show();
    return a.exec();
}
