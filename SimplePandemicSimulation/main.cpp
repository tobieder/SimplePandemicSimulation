#include "SimplePandemicSimulation.h"
#include <QtWidgets/QApplication>

#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/fonts/OpenSans/OpenSans-Regular.ttf");
    QFont font("Open Sans");
    font.setPointSizeF(8);
    a.setFont(font);

    SimplePandemicSimulation w;
    w.show();
    return a.exec();
}
