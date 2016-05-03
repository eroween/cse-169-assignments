
#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>
#include "mainwidget.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("CSE 169 - A1 - Skeleton");

//    MainWidget widget;
//    widget.show();
//    widget.load(argc > 1 ? argv[1] : "wasp.skel", argc > 2 ? argv[2] : "wasp.skin");

    MainWindow w(argc, argv);
    w.show();

    return app.exec();
}
