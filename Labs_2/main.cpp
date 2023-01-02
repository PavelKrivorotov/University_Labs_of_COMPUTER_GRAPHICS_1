#include <QApplication>

#include "scene.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);


    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(1, 0);
    format.setProfile(QSurfaceFormat::CoreProfile);


    Scene scene = Scene();
    scene.setFormat(format);
    scene.show();


    return a.exec();
}
