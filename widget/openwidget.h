#ifndef OPENWIDGET_H
#define OPENWIDGET_H
#include<QOpenGLWidget>
#include<QOpenGLFunctions_3_3_Compatibility>
#include<QOpenGLShader>
#include<QOpenGLShaderProgram>
#include"./include/Camera.h"

class OpenWidget  : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Compatibility
{
public:
    OpenWidget();
    ~OpenWidget() override;
    void keyPressEvent(QKeyEvent*)override;

private:
    GLuint VAO;
    GLuint VBO;
    GLuint _VAO;
    GLuint _VBO;
    QOpenGLShader* vshader;
    QOpenGLShader* fshader;
    QOpenGLShaderProgram* shaderProgram;
    QOpenGLShader* _vshader;
    QOpenGLShader* _fshader;
    QOpenGLShaderProgram* _shaderProgram;
    GLuint texture;
    GLuint texture1;
    GLuint texture2;
    GLuint texture3;
    GLuint texture4;
    QPoint prepoint;

    GLboolean keys[1024];//获取键盘按键，实现多键触控
    GLboolean isLineMode;
    void keyReleaseEvent(QKeyEvent *event);
protected:
    void paintGL() override;
    void initializeGL() override;
    void mouseMoveEvent(QMouseEvent*)override;
    void mousePressEvent(QMouseEvent*)override;
    void wheelEvent(QWheelEvent*)override;
    void mouseReleaseEvent(QMouseEvent *event);
private:
  void processInput(GLfloat dt);//摄像机键盘处理函数，
  void updateGL();//opengl 更新函数


  GLboolean isFirstMouse;
  GLboolean isLeftMousePress;
  GLint lastX;
  GLint lastY;

//  QTime time;
  GLfloat deltaTime;
  GLfloat lastFrame;//上一帧

  Camera *camera;
};

#endif // OPENWIDGET_H

