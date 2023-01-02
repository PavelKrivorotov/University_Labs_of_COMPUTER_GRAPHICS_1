#ifndef SCENE_H
#define SCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLFunctions_1_0>

#include <QTimer>


class Scene: public QOpenGLWidget, protected QOpenGLFunctions_1_0 {
    Q_OBJECT

public:
    Scene(QWidget *parent = nullptr);
    ~Scene();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

private:
    void drawPyramid();

    void updateAngles();

private:
    float _startAngleX;
    float _startAngleY;
    float _startAngleZ;

    QTimer *_timer;
};

#endif // SCENE_H
