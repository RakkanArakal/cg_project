#ifndef RENDERSCENE_H
#define RENDERSCENE_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QElapsedTimer>
#include <QKeyEvent>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <include/Camera.h>
#include <include/skybox.h>
#include <component/component.h>
#include <component/bezier.h>
#include <component/myslider.h>

class RenderScene: public QOpenGLWidget{
    Q_OBJECT

public:
    RenderScene(QWidget *partent);
    ~RenderScene();

    QPushButton *Load;
    QPushButton *Light;
    QPushButton *Flower;
    QPushButton *Quit;

    QPushButton *Clear;
    QPushButton* model1;
    QPushButton* model2;
    QPushButton* model3;
    QPushButton* model4;
    QPushButton* model5;
    QPushButton* model6;
    QPushButton* model7;
    QPushButton* model8;
    QPushButton* mode;

    MySlider *mySlider;

    QTimer timer;
    QElapsedTimer r_timer;

    QVector<QPoint> point,pointTmp;
    QVector<QPoint> bezier_point,bezierTmp;
    QVector<QPoint> light_point;
    int point_count ,cnt;
    bool isCamera,isFalling;

    QString textureNow,textureTmp;

    Camera *camera;
    Bezier *bezier;

//    Cube *light;
    Plane *floor;
    SkyBox *skybox;
    Rotator* light;

    GLboolean isFirstMouse,isBlinn,isLeftMousePress;
    GLint lastX,lastY;
    float phongShininess,blinnShininess;

    GLboolean keys[1024];
    void setSkyBoxPath(int index);
    void processInput(GLfloat dt);

    struct myModel
    {
        QString name;
        QVector3D translation;
        float scale;
        QVector<QPoint> bezier_point;
        QString textureNow;
        myModel(QString n,QVector3D t,float s,QVector<QPoint> b ,QString tex)
        {name = n; translation = t; scale = s; bezier_point = b; textureNow = tex;}
    };
    QMap<int,myModel*> modelMap;
    QMap<int,QPushButton*> buttonMap;
    QMap<int,bool> moveMap;

    struct myFlower
    {
        QVector3D translation;
        float dy;
        Plane *flower;
        myFlower(QVector3D t,float d,Plane *f)
        {translation = t; dy = d; flower = f;}
    };
    QMap<int,myFlower*> flowerMap;

    void preLoadPath(QString path);
    void clearBoard();
    void modelPush(int n);
public slots:

    void QuitPush(){this->close();}
    void changeLight();
    void slotTimeout(){this->update();}
    void load();
    void setLightValue();
    void clear();
    void flowersFalling(){isFalling = isFalling^true;}
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h){}
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);



};

#endif // RENDERSCENE_H
