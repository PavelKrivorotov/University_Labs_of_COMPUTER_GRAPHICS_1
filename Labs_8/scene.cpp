#include "scene.h"

#include "iostream"
#include "stdio.h"

Scene::Scene(QWidget *parent): QOpenGLWidget(parent) {

}


Scene::~Scene() {

}


void Scene::initializeGL() {
    initializeOpenGLFunctions();

    // NEED your FULL PATH to shader!! -- "D:/.../...")
    const char * text = loadFile(YOUR_PATH/shader1.txt);

    GLuint shader = initShader(text);
    logShader(shader);

    delete [] text;

    _Program = initProgram(shader);
    glUseProgram(_Program);

    //
    _windowSize = glGetUniformLocation(_Program, "windowSize");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


void Scene::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    //
    glUniform2f(_windowSize, (GLfloat)w, (GLfloat)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Scene::paintGL() {
    //Очищаем буферы цвета и глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Включаем буфер глубины
    glEnable(GL_DEPTH_TEST);

    //Профилактика))) (Которая спасает!)
    glLoadIdentity();

    drawTriangle();
}


void Scene::closeEvent(QCloseEvent *event) {
    qDebug() << "Clear Program!";
    clearProgram();
}


void Scene::drawTriangle() {
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}


const char * Scene::loadFile(const char *dir) {
    int lengthFile = 10000;
    char *text = new char[lengthFile];

    memset(text, 0, lengthFile);
    FILE *file;
    file = fopen(dir, "rb");

    if (file) {
        fread(text, 1, lengthFile, file);
        fclose(file);
    }

    return text;
}


GLuint Scene::initShader(const char *textProgram) {
    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &textProgram, NULL);
    glCompileShader(shader);

    return shader;
}


void Scene::logShader(GLuint shader) {
    GLint ok;
    GLchar log[2000];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);

    if (!ok) {
        glGetShaderInfoLog(shader, 2000, NULL, log);
        qDebug() << log;
    }
}


GLuint Scene::initProgram(GLuint shader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, shader);
    glLinkProgram(program);

    return program;
}


void Scene::clearProgram() {
    glUseProgram(0);
    glDeleteProgram(_Program);
}

