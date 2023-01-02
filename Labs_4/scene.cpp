#include "scene.h"

#include <QKeyEvent>


Scene::Scene(QWidget *parent): QOpenGLWidget(parent) {
    _startAngleX = 0;
    _startAngleY = 0;
    _startAngleZ = 0;


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
    delete [] _cubeWithColor;
    delete [] _cubeRedColor;
}


void Scene::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void Scene::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

//    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 2.0);
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

    //Устанавливаем источник света на позиции
    GLfloat position0[] = {-1.0f, 1.5f, -3.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, _lightWithColor);
    drawCube(GL_AMBIENT, _cubeWithColor, false, position0[0], position0[1], position0[2], 0.15);

    GLfloat position1[] = {0.0f, 1.5f, -3.5f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, _lightYellowColor);
    drawCube(GL_AMBIENT, _cubeWithColor, false, position1[0], position1[1], position1[2], 0.15);

    GLfloat position2[] = {1.0f, 1.5f, -3.0f, 1.0f};
    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, _lightSeaColor);
    drawCube(GL_AMBIENT, _cubeWithColor, false, position2[0], position2[1], position2[2], 0.15);

    //Рисуем кубы
    drawCube(GL_AMBIENT, _cubeMultyColor, true, -0.5, -0.25, -1.5);
    drawCube(GL_DIFFUSE, _cubeMultyColor, true, 0.0, 0.0, -2.0);
    drawCube(GL_SPECULAR, _cubeMultyColor, true, 0.5, -0.25, -1.5);

    //Очищаем источники света
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
}


void Scene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Left:
            _startAngleY -= 5;
            break;

        case Qt::Key_Up:
            _startAngleX -= 5;
            break;

        case Qt::Key_Right:
            _startAngleY += 5;
            break;

        case Qt::Key_Down:
            _startAngleX += 5;
            break;

        default:
            break;
    }

    update();
}


void Scene::drawPyramid(GLenum modeMaterial, float x0, float y0, float z0, float sx, float sy, float sz) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(x0, y0, z0); // влево/вправо, вверх/вниз, назад/вперед
    glRotatef(_startAngleX, 1.0f, 0.0f, 0.0f); // поворот на угол X
    glRotatef(_startAngleY, 0.0f, 1.0f, 0.0f); // поворот на угол Y
    glRotatef(_startAngleZ, 0.0f, 0.0f, 1.0f); // поворот на угол Z

    glScalef(sx, sy, sz);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glColorMaterial(GL_FRONT, modeMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.9f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, _materialBlue);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);


    GLfloat vertexs[] = {
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
    };

    GLuint indexs[] = {
        0, 1, 2,
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f
    };

    GLfloat normals[] = {
        -0.5f, -0.5f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -0.5f, -0.5f,
        -0.5f, 1.0f, -0.5f,
    };

    glVertexPointer(3, GL_FLOAT, 0, vertexs);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glNormalPointer(GL_FLOAT, 0, normals);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, indexs);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);

    glFlush();
}


void Scene::drawCube(GLenum modeMaterial, GLfloat *cubeColor,bool dinamicFigure, float x0, float y0,
                     float z0, float height, float sx, float sy, float sz) {

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(x0, y0, z0); // влево/вправо, вверх/вниз, назад/вперед

    if (dinamicFigure) {
        glRotatef(_startAngleX, 1.0f, 0.0f, 0.0f); // поворот на угол X
        glRotatef(_startAngleY, 0.0f, 1.0f, 0.0f); // поворот на угол Y
        glRotatef(_startAngleZ, 0.0f, 0.0f, 1.0f); // поворот на угол Z
    }

    glScalef(sx, sy, sz);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glColorMaterial(GL_FRONT, modeMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.2f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, _materialBlue);

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
    glColorPointer(3, GL_FLOAT, 0, cubeColor);
    glNormalPointer(GL_FLOAT, 0, normals);

    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, indexs);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);

    glFlush();
}


void Scene::updateAngles(float dx, float dy, float dz) {
    _startAngleX += dx;
    _startAngleY += dy;
    _startAngleZ += dz;

    update();
}

