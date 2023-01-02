#ifndef SCENE_H
#define SCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLFunctions_3_0>


class Scene: public QOpenGLWidget, protected QOpenGLFunctions_3_0 {
    Q_OBJECT

public:
    Scene(QWidget *parent = nullptr);
    ~Scene();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    void drawPyramid(GLenum modeMaterial = GL_AMBIENT, float x0 = 0.0, float y0 = 0.0, float z0 = 0.0,
                     float sx = 0.25, float sy = 0.25, float sz = 0.25);

    void drawCube(GLenum modeMaterial, GLfloat *cubeColor, bool dinamicFigure = true,
                  float x0 = 0.0, float y0 = 0.0, float z0 = 0.0, float height = 0.5,
                  float sx = 0.25, float sy = 0.25, float sz = 0.25);

    void updateAngles(float dx, float dy, float dz);

private:
    float _startAngleX;
    float _startAngleY;
    float _startAngleZ;

    GLfloat *_lightWithColor;
    GLfloat *_lightYellowColor;
    GLfloat *_lightSeaColor;
    GLfloat *_lightBlackColor;

    GLfloat *_materialWith;
    GLfloat *_materialBlack;
    GLfloat *_materialYellow;
    GLfloat *_materialBlue;
    GLfloat *_materialGreen;

    GLfloat *_cubeMultyColor;
    GLfloat *_cubeWithColor;
    GLfloat *_cubeRedColor;
};

#endif // SCENE_H
