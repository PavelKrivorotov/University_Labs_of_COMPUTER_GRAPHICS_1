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

    void closeEvent(QCloseEvent *event) override;

    void drawTriangle();

    const char * loadFile(const char *dir);

    GLuint initShader(const char *textProgram);

    void logShader(GLuint shader);

    GLuint initProgram(GLuint shader);

    void clearProgram();

private:
    GLuint _Program;
    GLint _Unif_color;

    GLint _windowSize;
};

#endif // SCENE_H
