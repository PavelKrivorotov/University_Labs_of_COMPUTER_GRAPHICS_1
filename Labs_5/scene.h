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
    void drawRect(GLenum modeMaterial, GLfloat *rectColor, float x0 = 0.0, float y0 = 0.0,
                  float z0 = 0.0, float height = 0.5, float angleY0 = 0, float sx = 0.25,
                  float sy = 0.25, float sz = 0.25);

    void drawCube(GLenum modeMaterial, GLfloat *cubeColor, int number, bool dinamicFigure = true,
                  float x0 = 0.0, float y0 = 0.0, float z0 = 0.0, float height = 0.5,
                  float sx = 0.25, float sy = 0.25, float sz = 0.25);

private:
    int _currentIndexLight;

    float _startAngleY0;
    float _startAngleY1;
    float _startAngleY2;

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
    GLfloat *_cubeMultyColorAlpha;

    GLfloat *_cubeWithColor;
    GLfloat *_cubeWithColorAlpha;

    GLfloat *_cubeRedColor;
    GLfloat *_cubeRedColorAlpha;

    GLfloat *_rectGreenColorAlpha;
};

#endif // SCENE_H
