#include "scene.h"

Scene::Scene(QWidget *parent): QOpenGLWidget(parent) {
    _startAngleX = 0;
    _startAngleY = 0;
    _startAngleZ = 0;

    _timer = new QTimer();

    connect(_timer, &QTimer::timeout, this, &Scene::updateAngles);
}


Scene::~Scene() {
    delete _timer;
}


void Scene::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    _timer->start(120);
}


void Scene::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Scene::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    drawPyramid();
}


void Scene::drawPyramid() {
    // трехмерность
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.5f, 0.0f, 0.0f); // влево/вправо, вверх/вниз, назад/вперед
    glRotatef(_startAngleX, 1.0f, 0.0f, 0.0f); // поворот на угол X
    glRotatef(_startAngleY, 0.0f, 1.0f, 0.0f); // поворот на угол Y
    glRotatef(_startAngleZ, 0.0f, 0.0f, 1.0f); // поворот на угол Z

    //нижняя сторона
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-0.5f, 0.0f, -0.5f);
        glVertex3f(0.5f, 0.0f, -0.5f);
        glVertex3f(0.5f, 0.0f, 0.5f);
        glVertex3f(-0.5f, 0.0f, 0.5f);
   glEnd();

    //1-ая боковая сторона
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, 0.0f, -0.5f);
        glVertex3f(-0.5f, 0.0f, 0.5f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

   //2-ая боковая сторона
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.5f, 0.0f, -0.5f);
        glVertex3f(0.5f, 0.0f, -0.5f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

   //3-я боковая сторона
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.5f, 0.0f, 0.5f);
        glVertex3f(0.5f, 0.0f, -0.5f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

   //4-я боковая сторона
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.0f, 0.5f);
        glVertex3f(0.5, 0.0f, 0.5f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    glFlush();
}


void Scene::updateAngles() {
//    _startAngleX += 5;
    _startAngleY += 5;
//    _startAngleZ += 5;

    update();
}

