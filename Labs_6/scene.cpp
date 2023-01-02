#include "scene.h"

#include <QKeyEvent>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Scene::Scene(QWidget *parent): QOpenGLWidget(parent) {
    _startAngleY = 0;


    _indexCube = 0;
    _heightCube = 0.5;

    _indexPyramid = 0;
    _heightPyramid = 0.5;

    _indexCubeTexture = 0;
    _indexPyramidTexture = 0;
    _indexNurbs = 0;


    _lightWithColor = new GLfloat[4] { 1.0f, 1.0f, 1.0f, 1.0f };
    _lightYellowColor = new GLfloat[4] { 1.0f, 1.0f, 0.0f, 1.0f };
    _lightSeaColor = new GLfloat[4] { 0.0f, 1.0f, 1.0f, 1.0f };
    _lightBlackColor = new GLfloat[4] { 0.0f, 0.0f, 0.0f, 1.0f };


    _materialWith = new GLfloat[4] { 1.0f, 1.0f, 1.0f, 1.0f };
    _materialBlack = new GLfloat[4] { 0.0f, 0.0f, 0.0f, 1.0f };
    _materialYellow = new GLfloat[4] { 1.0f, 1.0f, 0.0f, 1.0f };
    _materialBlue = new GLfloat[4] { 0.0f, 0.0f, 1.0f, 1.0f };
    _materialGreen = new GLfloat[4] { 0.0f, 1.0f, 0.0f, 1.0f };


    _fogState = false;


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
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
    };

    _pyramidMultyColorAlpha = new GLfloat[20] {
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
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


    _fogGreyColor = new GLfloat[4] { 1.0f, 1.0f, 1.0f, 1.0f };
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
    delete [] _pyramidMultyColorAlpha;

    delete [] _cubeWithColor;
    delete [] _cubeWithColorAlpha;

    delete [] _cubeRedColor;
    delete [] _cubeRedColorAlpha;

    delete [] _rectGreenColorAlpha;

    delete [] _fogGreyColor;
}


void Scene::initializeGL() {
    initializeOpenGLFunctions();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Load texture (NEED your FULL PATH to photo! -- "D:/.../...")
    loadTexture(_indexCubeTexture, YOUR_PATH/house_wall.png);
    loadTexture(_indexPyramidTexture, YOUR_PATH/house_roof.png);
    loadTexture(_indexNurbsTexture, YOUR_PATH/test.jpg);

    //Create a list of cube
    _indexCube = glGenLists(1);
    glNewList(_indexCube, GL_COMPILE);
    drawCube(GL_AMBIENT, _cubeWithColorAlpha, 0, false);
    glEndList();

    //Create a list of pyramid
    _indexPyramid = glGenLists(1);
    glNewList(_indexPyramid, GL_COMPILE);
    drawPyramid(GL_AMBIENT, _cubeWithColorAlpha, 0, false);
    glEndList();

    //Create a lists of NURBS
    _indexNurbs = glGenLists(1);
    glNewList(_indexNurbs, GL_COMPILE);
    drawNurbs(GL_AMBIENT, _cubeWithColorAlpha, 0, false);
    glEndList();

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
}


void Scene::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

//    glFrustum(-0.7, 0.7, -0.7, 0.7, 1.0, 8.0);
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 8.0);

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

    //Устанавливаем источник света на позиции
    GLfloat position[] = {2.0f, 1.5f, 0.0f, 1.0f};
    enableLight(GL_DIFFUSE, _lightWithColor, position);

    showHouse(0.0, 1.0, -2.5, 0, true, 0.0, 0.5, 0.5, 0.5);
    showNurbs(_indexNurbsTexture, 0.0, 0.0, -2.5, true, 0.0, 0.6, 0.6, 0.6);

    if (_fogState) { enableFog(GL_EXP, _fogGreyColor, 0.25f, 2.0f, 8.0f); }
    else { disableFog(); }
}


void Scene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_1:
            _fogState = true;
            break;

        case Qt::Key_2:
            _fogState = false;
            break;

        case Qt::Key_Left:
            _startAngleY -= 5;
            break;

        case Qt::Key_Right:
            _startAngleY += 5;
            break;

        default:
            break;
    }

    update();
}


void Scene::loadTexture(GLuint &indexTexture, const char *path) {
    int width, height, n;
    unsigned char *data = stbi_load(path, &width, &height, &n, 0);

    if (data) {
        glGenTextures(1, &indexTexture);
        glBindTexture(GL_TEXTURE_2D, indexTexture);

//            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }
}


void Scene::showPyramid(GLuint index, float x0, float y0, float z0, float yAngle, float sx,
                        float sy, float sz) {
    glLoadIdentity();

    glTranslatef(x0, y0, z0);
    glRotatef(yAngle, 0.0, 1.0, 0.0);
    glScalef(sx, sy, sz);

    glCallList(index);
}


void Scene::showCube(GLuint index, float x0, float y0, float z0, float yAngle, float sx,
                     float sy, float sz) {
    glLoadIdentity();

    glTranslatef(x0, y0, z0);
    glRotatef(yAngle, 0.0, 1.0, 0.0);
    glScalef(sx, sy, sz);

    glCallList(index);
}


void Scene::showNurbs(GLuint index, float x0, float y0, float z0, bool dinamicFigure,
                      float yAngle, float sx, float sy, float sz) {
    glLoadIdentity();

    if (dinamicFigure) { yAngle += _startAngleY; }

    glTranslatef(x0, y0, z0);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glScalef(sx, sy, sz);

    glCallList(index);
}


void Scene::showHouse(float x0, float y0, float z0, int number, bool dinamicFigure,
                      float yAngle, float sx, float sy, float sz) {

    if (dinamicFigure) { yAngle += _startAngleY; }

    showCube(_indexCube, x0, y0, z0, yAngle, sx, sy, sz);
    showPyramid(_indexPyramid, x0, y0 + 0.5 * sy, z0, yAngle, sx, sy, sz);
}


void Scene::drawPyramid(GLenum modeMaterial, GLfloat *pyramidColor, int number, bool dinamicFigure) {
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _indexPyramidTexture);

    glColorMaterial(GL_FRONT, modeMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.2f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, _materialBlack);


    GLfloat deltaHeight = _heightPyramid * 0.25;

    //Передняя сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glNormal3f(0.0f, deltaHeight, 1.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-(_heightPyramid + deltaHeight), 0.0f, _heightPyramid + deltaHeight);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(_heightPyramid + deltaHeight, 0.0f, _heightPyramid + deltaHeight);

        glTexCoord2f(0.2f, 0.0f);
        glVertex3f(_heightPyramid - deltaHeight, _heightPyramid, _heightPyramid - deltaHeight);

        glTexCoord2f(0.8f, 0.0f);
        glVertex3f(-(_heightPyramid - deltaHeight), _heightPyramid, _heightPyramid - deltaHeight);
    glEnd();

    //Левая сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glNormal3f(-1.0f, deltaHeight, 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-(_heightPyramid + deltaHeight), 0.0f, -(_heightPyramid + deltaHeight));

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-(_heightPyramid + deltaHeight), 0.0f, _heightPyramid + deltaHeight);

        glTexCoord2f(0.2f, 0.0f);
        glVertex3f(-(_heightPyramid - deltaHeight), _heightPyramid, _heightPyramid - deltaHeight);

        glTexCoord2f(0.8f, 0.0f);
        glVertex3f(-(_heightPyramid - deltaHeight), _heightPyramid, -(_heightPyramid - deltaHeight));
    glEnd();

    //Задняя сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glNormal3f(0.0f, deltaHeight, -1.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(_heightPyramid + deltaHeight, 0.0f, -(_heightPyramid + deltaHeight));

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-(_heightPyramid + deltaHeight), 0.0f, -(_heightPyramid + deltaHeight));

        glTexCoord2f(0.2f, 0.0f);
        glVertex3f(-(_heightPyramid - deltaHeight), _heightPyramid, -(_heightPyramid - deltaHeight));

        glTexCoord2f(0.8f, 0.0f);
        glVertex3f(_heightPyramid - deltaHeight, _heightPyramid, -(_heightPyramid - deltaHeight));
    glEnd();

    //Правая сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glNormal3f(1.0f, deltaHeight, 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(_heightPyramid + deltaHeight, 0.0f, _heightPyramid + deltaHeight);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(_heightPyramid + deltaHeight, 0.0f, -(_heightPyramid + deltaHeight));

        glTexCoord2f(0.2f, 0.0f);
        glVertex3f(_heightPyramid - deltaHeight, _heightPyramid, -(_heightPyramid - deltaHeight));

        glTexCoord2f(0.8f, 0.0f);
        glVertex3f(_heightPyramid - deltaHeight, _heightPyramid, _heightPyramid - deltaHeight);
    glEnd();

    //Верхняя сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glNormal3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-(_heightPyramid - deltaHeight), _heightPyramid, _heightPyramid - deltaHeight);

        glNormal3f(1.0f, 1.0f, 1.0f);
        glVertex3f(_heightPyramid - deltaHeight, _heightPyramid, _heightPyramid - deltaHeight);

        glNormal3f(1.0f, 1.0f, -1.0f);
        glVertex3f(_heightPyramid - deltaHeight, _heightPyramid, -(_heightPyramid - deltaHeight));

        glNormal3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-(_heightPyramid - deltaHeight), _heightPyramid, -(_heightPyramid - deltaHeight));
    glEnd();

    //Нижняя сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glNormal3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-(_heightPyramid + deltaHeight), 0.0f, _heightPyramid + deltaHeight);

        glNormal3f(1.0f, -1.0f, 1.0f);
        glVertex3f(_heightPyramid + deltaHeight, 0.0f, _heightPyramid + deltaHeight);

        glNormal3f(1.0f, -1.0f, -1.0f);
        glVertex3f(_heightPyramid + deltaHeight, 0.0f, -(_heightPyramid + deltaHeight));

        glNormal3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-(_heightPyramid + deltaHeight), 0.0f, -(_heightPyramid + deltaHeight));
    glEnd();


    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFlush();
}


void Scene::drawCube(GLenum modeMaterial, GLfloat *cubeColor, int number, bool dinamicFigure) {
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _indexCubeTexture);

    glColorMaterial(GL_FRONT, modeMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.3f);
    glMaterialfv(GL_FRONT, GL_SPECULAR, _materialBlack);


    //Передняя сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-_heightCube, -_heightCube, _heightCube);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(_heightCube, -_heightCube, _heightCube);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(_heightCube, _heightCube, _heightCube);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-_heightCube, _heightCube, _heightCube);
    glEnd();

    //Левая сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glNormal3f(-1.0f, 0.0f, 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-_heightCube, -_heightCube, -_heightCube);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-_heightCube, -_heightCube, _heightCube);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-_heightCube, _heightCube, _heightCube);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-_heightCube, _heightCube, -_heightCube);
    glEnd();

    //Задняя сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glNormal3f(0.0f, 0.0f, -1.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(_heightCube, -_heightCube, -_heightCube);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-_heightCube, -_heightCube, -_heightCube);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-_heightCube, _heightCube, -_heightCube);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(_heightCube, _heightCube, -_heightCube);
    glEnd();

    //Правая сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glNormal3f(1.0f, 0.0f, 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(_heightCube, -_heightCube, _heightCube);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(_heightCube, -_heightCube, -_heightCube);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(_heightCube, _heightCube, -_heightCube);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(_heightCube, _heightCube, _heightCube);
    glEnd();

    //Нижняя сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glNormal3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-_heightCube, -_heightCube, _heightCube);

        glNormal3f(1.0f, -1.0f, 1.0f);
        glVertex3f(_heightCube, -_heightCube, _heightCube);

        glNormal3f(1.0f, -1.0f, -1.0f);
        glVertex3f(_heightCube, -_heightCube, -_heightCube);

        glNormal3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-_heightCube, -_heightCube, -_heightCube);
    glEnd();

    //Верхняя сторона
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glNormal3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-_heightCube, _heightCube, _heightCube);

        glNormal3f(1.0f, 1.0f, 1.0f);
        glVertex3f(_heightCube, _heightCube, _heightCube);

        glNormal3f(1.0f, 1.0f, -1.0f);
        glVertex3f(_heightCube, _heightCube, -_heightCube);

        glNormal3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-_heightCube, _heightCube, -_heightCube);
    glEnd();


    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFlush();
}


void Scene::drawNurbs(GLenum modeMaterial, GLfloat *nurbsColor, int number, bool dinamicFigure) {
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_MAP2_TEXTURE_COORD_2);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _indexNurbsTexture);

    glEvalMesh2(GL_FILL, 0, 20, 0, 20);

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &_ctrlpoints[0][0][0]);
    glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &_texpts[0][0][0]);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glColorMaterial(GL_FRONT, modeMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.3f);
    glMaterialfv(GL_FRONT, GL_SPECULAR, _materialBlack);


    glColor4f(1.0, 1.0, 1.0, 1.0);

    for (int j = 0; j <= 8; j++) {
       glBegin(GL_LINE_STRIP);
           for (int i = 0; i <= 30; i++)
              glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
       glEnd();

       glBegin(GL_LINE_STRIP);
           for (int i = 0; i <= 30; i++)
              glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
       glEnd();
    }


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);

    glDisable(GL_MAP2_VERTEX_3);
    glDisable(GL_MAP2_TEXTURE_COORD_2);

    glFlush();
}


void Scene::enableLight(GLenum modeLight, GLfloat *lightColor, GLfloat *position) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, modeLight, lightColor);
}


void Scene::enableFog(GLenum modeFog, GLfloat *colorFog, GLfloat densityFog, GLfloat startCoord,
                      GLfloat endCoord) {

    glEnable(GL_FOG);

    glFogi(GL_FOG_MODE, modeFog);
    glFogfv(GL_FOG_COLOR, colorFog);
    glFogf(GL_FOG_DENSITY, densityFog);

    glHint(GL_FOG_HINT, GL_DONT_CARE);

    glFogf(GL_FOG_START, startCoord);
    glFogf(GL_FOG_END, endCoord);
}


void Scene::disableFog() {
    glDisable(GL_FOG);
}

