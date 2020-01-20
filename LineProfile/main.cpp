#include "stdafx.h"
#include "LineProfile.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LineProfile w;
    w.show();
    return a.exec();
}
