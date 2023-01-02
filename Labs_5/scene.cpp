#include "scene.h"

#include <QKeyEvent>


Scene::Scene(QWidget *parent): QOpenGLWidget(parent) {
    _currentIndexLight = 0;

    _startAngleY0 = 0;
    _startAngleY1 = 0;
    _startAngleY2 = 0;


    _lightWithColor = new GLfloat[4] {1.0f, 1.0f, 1.0f, 1.0f};
    _lightYellowColor = new GLfloat[4] {1.0f, 1.0f, 0.0f, 1.0f};
    _lightSeaColor = new GLfloat[4] {0.0f, 1.0f, 1.0f, 1.0f};
    _lightBlackColor = new GLfloat[4] {0.0f, 0.0f, 0.0f, 1.0f};


    _materialWith = new GLfloat[4] { 1.0f, 1.0f, 1.0f, 1.0f };
    _materialBlack = new GLfloat[4] { 0.0f, 0.0f, 0.0f, 1.0f };
    _materialYellow = new GLfloat[4] { 1.0f, 1.0f, 0.0f, 1.0f };
    _materialBlue = new GLfloat[4] { 0.0f, 0.0f, 1.0f, 1.0f };
    _materialGreen = new GLfloat[4] { 0.0f, 1.0f, 0.0f, 1.0f };


    _cubeMultyColor = new GLfloat[24] {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };

    _cubeMultyColorAlpha = new GLfloat[32] {
        1.0f, 0.0f, 0.0f, 0.6f,
        0.0f, 1.0f, 0.0f, 0.6f,
        1.0f, 0.0f, 0.0f, 0.6f,
        0.0f, 1.0f, 0.0f, 0.6f,

        0.0f, 1.0f, 0.0f, 0.6f,
        1.0f, 0.0f, 0.0f, 0.6f,
        0.0f, 1.0f, 0.0f, 0.6f,
        1.0f, 0.0f, 0.0f, 0.6f,
    };

    _cubeWithColor = new GLfloat[24] {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
    };

    _cubeWithColorAlpha = new GLfloat[32] {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };

    _cubeRedColor = new GLfloat[24] {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };

    _cubeRedColorAlpha = new GLfloat[32] {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
    };


    _rectGreenColorAlpha = new GLfloat[16] {
        0.0f, 1.0f, 0.0f, 0.3f,
        0.0f, 1.0f, 0.0f, 0.3f,
        0.0f, 1.0f, 0.0f, 0.3f,
        0.0f, 1.0f, 0.0f, 0.3f,
    };
}


Scene::~Scene() {
    delete [] _lightWithColor;
    delete [] _lightYellowColor;
    delete [] _lightSeaColor;
    delete [] _lightBlackColor;

    delete [] _materialWith;
    delete [] _materialBlack;
    delete [] _materialYellow;
    delete [] _materialBlue;
    delete [] _materialGreen;

    delete [] _cubeMultyColor;
    delete [] _cubeMultyColorAlpha;

    delete [] _cubeWithColor;
    delete [] _cubeWithColorAlpha;

    delete [] _cubeRedColor;
    delete [] _cubeRedColorAlpha;

    delete [] _rectGreenColorAlpha;
}


void Scene::initializeGL() {
    initializeOpenGLFunctions();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glDisable(GL_CULL_FACE);

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
}


void Scene::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-0.7, 0.7, -0.7, 0.7, 1.0, 8.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Scene::paintGL() {
    //Очищаем буферы цвета и глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Спасение!!))
    glLoadIdentity();

    //Включаем буфер глубины
    glEnable(GL_DEPTH_TEST);

    //Включаем свет
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

//    //Устанавливаем источник света на позиции
    GLfloat position0[] = {-1.0f, 1.5f, -3.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, _lightWithColor);
    drawCube(GL_AMBIENT, _cubeWithColorAlpha, 0, true, position0[0], position0[1], position0[2], 0.15);

    GLfloat position1[] = {0.0f, 1.5f, -3.5f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, _lightYellowColor);
    drawCube(GL_AMBIENT, _cubeWithColorAlpha, 1, true, position1[0], position1[1], position1[2], 0.15);

    GLfloat position2[] = {1.0f, 1.5f, -3.0f, 1.0f};
    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, _lightSeaColor);
    drawCube(GL_AMBIENT, _cubeWithColorAlpha, 2, true, position2[0], position2[1], position2[2], 0.15);

    //Рисуем левый задний кубик
    drawCube(GL_DIFFUSE, _cubeMultyColorAlpha, 4, false, 0.0, -0.25, -2.5);

    //Рисуем правый задний кубик
    drawCube(GL_SPECULAR, _cubeWithColorAlpha, 5, false, 0.5, -0.25, -2.5, 0.6);

    //Рисуем левый передний кубик
    drawCube(GL_AMBIENT, _cubeMultyColorAlpha, 3, false, -0.25, -0.25, -2.0, 0.75);

    //Рисуем правый передний квадрат (под углом)
    drawRect(GL_AMBIENT, _rectGreenColorAlpha, 0.35, -0.15, -1.0, 1.2, 20);

    //Очищаем источники света
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
}


void Scene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_1:
            _currentIndexLight = 0;
            break;

        case Qt::Key_2:
            _currentIndexLight = 1;
            break;

        case Qt::Key_3:
            _currentIndexLight = 2;
            break;

        default:
            if (event->key() == Qt::Key_Left) {
                if (_currentIndexLight == 0) { _startAngleY0 += 5; }
                else if (_currentIndexLight == 1) { _startAngleY1 += 5; }
                else { _startAngleY2 += 5; }
            }

            else if (event->key() == Qt::Key_Right) {
                if (_currentIndexLight == 0) { _startAngleY0 -= 5; }
                else if (_currentIndexLight == 1) { _startAngleY1 -= 5; }
                else { _startAngleY2 -= 5; }
            }

            break;
    }

    update();
}


void Scene::drawRect(GLenum modeMaterial, GLfloat *rectColor, float x0, float y0, float z0,
                     float height, float angleY, float sx, float sy, float sz) {

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(x0, y0, z0);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glScalef(sx, sy, sz);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glColorMaterial(GL_FRONT, modeMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.2f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, _materialBlue);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);


    GLfloat vertexs[] = {
        -height, -height, z0,
        -height, height, z0,
        height, height, z0,
        height, -height, z0,
    };

    GLuint indexs[] = {
        0, 1, 2, 3,
    };

    GLfloat colors[] = {

    };

    GLfloat normals[] = {
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
    };


    glVertexPointer(3, GL_FLOAT, 0, vertexs);
    glColorPointer(4, GL_FLOAT, 0, rectColor);
    glNormalPointer(GL_FLOAT, 0, normals);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, indexs);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);

    glFlush();
}


void Scene::drawCube(GLenum modeMaterial, GLfloat *cubeColor, int number, bool dinamicFigure,
                     float x0, float y0, float z0, float height, float sx, float sy, float sz) {

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, 0.0f);

    if (dinamicFigure) {
        switch (number) {
            case 0:
                glRotatef(_startAngleY0, 0.0f, 1.0f, 0.0f); // поворот на угол Y
                break;

            case 1:
                glRotatef(_startAngleY1, 0.0f, 1.0f, 0.0f); // поворот на угол Y
                break;

            case 2:
                glRotatef(_startAngleY2, 0.0f, 1.0f, 0.0f); // поворот на угол Y
                break;

            default:
                break;
        }
    }

    glTranslatef(x0, y0, z0); // влево/вправо, вверх/вниз, назад/вперед

    glScalef(sx, sy, sz);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glColorMaterial(GL_FRONT, modeMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.2f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, _materialBlue);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);


    GLfloat vertexs[] = {
        -height, -height, height,
        -height, -height, -height,
        height, -height, -height,
        height, -height, height,

        -height, height, height,
        -height, height, -height,
        height, height, -height,
        height, height, height,
    };

    GLuint indexs[] = {
        0, 1, 2, 3,

        0, 4, 5, 1,
        1, 5, 6, 2,
        2, 6, 7, 3,
        3, 7, 4, 0,

        4, 5, 6, 7,
    };

    GLfloat colors[] = {

    };

    GLfloat normals[] = {
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
    };


    glVertexPointer(3, GL_FLOAT, 0, vertexs);

    glColorPointer(4, GL_FLOAT, 0, cubeColor);
//    glColorPointer(3, GL_FLOAT, 0, cubeColor);

    glNormalPointer(GL_FLOAT, 0, normals);

    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, indexs);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);

    glFlush();
}

