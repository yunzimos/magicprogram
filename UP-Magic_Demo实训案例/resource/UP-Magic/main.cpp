#include <QtGui/QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.showFullScreen();
    a.setFont(QFont("wenquanyi",12));

    return a.exec();
}
