#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>


int main(int argc, char *argv[])
{
    // 1. 请求 Desktop OpenGL 4.1 Core
    QSurfaceFormat format;

    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);

    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    // macOS 上非常重要：
    // 必须在 QApplication 创建之前设置
    QSurfaceFormat::setDefaultFormat(format);

    // 2. 然后才能创建 QApplication
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
