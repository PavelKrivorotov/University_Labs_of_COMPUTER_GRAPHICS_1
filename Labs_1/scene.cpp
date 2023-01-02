#include "scene.h"

Scene::Scene(QWidget *parent): QOpenGLWidget(parent) {

}


Scene::~Scene() {

}


void Scene::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


void Scene::resizeGL(int w, int h) {

}


void Scene::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawTriangle();
}


void Scene::drawTriangle() {
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.8f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.0f);
    glEnd();
}

