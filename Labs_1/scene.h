#ifndef SCENE_H
#define SCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLFunctions_1_0>


class Scene: public QOpenGLWidget, protected QOpenGLFunctions_1_0 {

public:
    Scene(QWidget *parent = nullptr);
    ~Scene();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void drawTriangle();
};

#endif // SCENE_H
