#ifndef SCENE_H
#define SCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLFunctions_3_0>

#include <QTimer>


class Scene: public QOpenGLWidget, protected QOpenGLFunctions_3_0 {
    Q_OBJECT

public:
    Scene(QWidget *parent = nullptr);
    ~Scene();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

private:
    void drawPyramid(GLenum modeMaterial = GL_AMBIENT, float x0 = 0.0, float y0 = 0.0, float z0 = 0.0,
                     float sx = 0.25, float sy = 0.25, float sz = 0.25);

    void drawCube(GLenum modeMaterial, GLfloat *cubeColor,
                  float x0 = 0.0, float y0 = 0.0, float z0 = 0.0,
                  float sx = 0.25, float sy = 0.25, float sz = 0.25);

    void updateAngles();

private:
    float _startAngleX;
    float _startAngleY;
    float _startAngleZ;

    GLfloat *_materialWith;
    GLfloat *_materialBlack;
    GLfloat *_materialYellow;
    GLfloat *_materialBlue;
    GLfloat *_materialGreen;

    GLfloat *_cubeMultyColor;
    GLfloat *_cubeWithColor;
    GLfloat *_cubeRedColor;

    QTimer *_timer;
};

#endif // SCENE_H
