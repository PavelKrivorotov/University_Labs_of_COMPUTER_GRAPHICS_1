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
    void loadTexture(GLuint &indexTexture, const char *path);

    void showPyramid(GLuint index, float x0, float y0, float z0, float yAngle = 0.0, float sx = 1.0,
                  float sy = 1.0, float sz = 1.0);

    void showCube(GLuint index, float x0, float y0, float z0, float yAngle = 0.0, float sx = 1.0,
                  float sy = 1.0, float sz = 1.0);

    void showNurbs(GLuint index, float x0, float y0, float z0, bool dinamicFigure, float yAngle = 0.0,
                   float sx = 1.0, float sy = 1.0, float sz = 1.0);

    void showHouse(float x0, float y0, float z0, int number = -1, bool dinamicFigure = false,
                   float yAngle = 0.0, float sx = 1.0, float sy = 1.0, float sz = 1.0);

    void drawPyramid(GLenum modeMaterial, GLfloat *pyramidColor, int number, bool dinamicFigure = true);

    void drawCube(GLenum modeMaterial, GLfloat *cubeColor, int number, bool dinamicFigure = true);

    void drawNurbs(GLenum modeMaterial, GLfloat *nurbsColor, int number, bool dinamicFigure = true);

    void drawHouseShadow(float x0, float y0, float z0, int yAngle = 0, float sx = 1.0,
                        float sy = 1.0, float sz = 1.0);

    void enableLight(GLenum modeLight, GLfloat *lightColor, GLfloat *position);

    void enableFog(GLenum modeFog, GLfloat *colorFog, GLfloat densityFog, GLfloat startCoord,
                   GLfloat endCoord);

    void disableFog();

private:
    float _startAngleY;

    GLuint _indexCube;
    float _heightCube;

    GLuint _indexPyramid;
    float _heightPyramid;

    GLuint _indexNurbs;
    GLfloat _ctrlpoints[4][4][3] = {
        {{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},
         {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
        {{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},
         {0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
        {{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0},
         {0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
        {{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},
         {0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
    };
    GLfloat _texpts[2][2][2] = {
        {{0.0, 0.0}, {0.0, 1.0}},
        {{1.0, 0.0}, {1.0, 1.0}}
    };

    bool _fogState;

    GLuint _indexCubeTexture;
    GLuint _indexPyramidTexture;
    GLuint _indexNurbsTexture;

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
    GLfloat *_pyramidMultyColorAlpha;

    GLfloat *_cubeWithColor;
    GLfloat *_cubeWithColorAlpha;

    GLfloat *_cubeRedColor;
    GLfloat *_cubeRedColorAlpha;

    GLfloat *_rectGreenColorAlpha;

    GLfloat *_fogGreyColor;
};

#endif // SCENE_H
