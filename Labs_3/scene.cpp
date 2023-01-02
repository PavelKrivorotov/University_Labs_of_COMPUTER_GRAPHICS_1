#include "scene.h"

Scene::Scene(QWidget *parent): QOpenGLWidget(parent) {
    _startAngleX = 0;
    _startAngleY = 0;
    _startAngleZ = 0;


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


    _timer = new QTimer();

    connect(_timer, &QTimer::timeout, this, &Scene::updateAngles);
}


Scene::~Scene() {
    delete [] _materialWith;
    delete [] _materialBlack;
    delete [] _materialYellow;
    delete [] _materialBlue;
    delete [] _materialGreen;

    delete [] _cubeMultyColor;
    delete [] _cubeWithColor;
    delete [] _cubeRedColor;

    delete _timer;
}


void Scene::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    _timer->start(90);
}


void Scene::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Scene::paintGL() {
    //Очищаем буферы цвета и глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Подгружаем спасение!!))
    glLoadIdentity();

    //Включаем буфер глубины
    glEnable(GL_DEPTH_TEST);

    //Включаем свет
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //Устанавливаем источник света на позицию
    GLfloat position[] = {0.0f, 0.0f, 10.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    //Назначаем свет источника
    glLightfv(GL_LIGHT0, GL_AMBIENT, _materialBlack);


    drawCube(GL_AMBIENT, _cubeMultyColor, -0.5, 0.5);
    drawCube(GL_DIFFUSE, _cubeMultyColor, 0.0, 0.5);
    drawCube(GL_SPECULAR, _cubeMultyColor, 0.5, 0.5);

    drawCube(GL_AMBIENT, _cubeWithColor, -0.5, 0.0);
    drawCube(GL_DIFFUSE, _cubeWithColor, 0.0, 0.0);
    drawCube(GL_SPECULAR, _cubeWithColor, 0.5, 0.0);

    drawCube(GL_AMBIENT, _cubeRedColor, -0.5, -0.5);
    drawCube(GL_DIFFUSE, _cubeRedColor, 0.0, -0.5);
    drawCube(GL_SPECULAR, _cubeRedColor, 0.5, -0.5);


    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
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


void Scene::drawCube(GLenum modeMaterial, GLfloat *cubeColor, float x0, float y0,
                     float z0, float sx, float sy, float sz) {

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
//    glMaterialf(GL_FRONT, GL_SHININESS, 0.2f);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, _materialBlue);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);


    GLfloat vertexs[] = {
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
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


void Scene::updateAngles() {
    _startAngleX += 10;
    _startAngleY += 5;
    _startAngleZ -= 7.5;

    update();
}

