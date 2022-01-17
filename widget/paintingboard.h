#ifndef PAINTINGBOARD_H
#define PAINTINGBOARD_H

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
#include <QMessageBox>
#include <include/Camera.h>
#include <component/component.h>
#include <component/bezier.h>
#include <resourcemangager/model.h>
class PaintingBoard: public QOpenGLWidget
{
    Q_OBJECT
public:
    PaintingBoard(QWidget *partent);
    ~PaintingBoard();

    QPushButton *Save;
    QPushButton *Load;
    QPushButton *Clear;
    QPushButton *Quit;

    QLabel *SaveL;
    QLabel *LoadL;
    QLabel *ClearL;
    QLabel *QuitL;

    QPushButton* backgroundTex;
    QPushButton* x_rotation;
    QPushButton* porcelainTex1;
    QPushButton* porcelainTex2;
    QPushButton* woodTex1;
    QPushButton* woodTex2;
    QPushButton* stoneTex1;
    QPushButton* stoneTex2;

    QFont   ft;
    QTimer time;
    QElapsedTimer *pre_timer;
    float rotate_time;

    QVector<QPoint> point,pointTmp;
    QVector<QPoint> bezier_point,bezierTmp;
    QPoint startPt, endPt, Pt;
    int point_count ,now,cnt;
    bool right_move,isCtrl,isRotate;
    QString textureNow,textureTmp;
    QString backgroundNow;

    Camera *camera;
    Bezier *bezier;

    Plane *plane;
    Point *ctrlPoint;
    Line *line;
    Rotator *rotator;
    Model *unicorn;

    typedef struct
    {
        QVector<QPoint> point;
        int point_count;
        QString textureNow;
    } PointPre;
    QMap<QString,PointPre> preMap;

    void preLoadModel();
    void preLoadPath(QString path);
public slots:

    void QuitPush(){this->close();}
    void slotTimeout(){
        if(isRotate) rotate_time = (rotate_time+0.75f);
        this->update();
    }
    void save();
    void changeBackground(){
        if(backgroundNow == "whitepaper1")
            backgroundNow = "whitepaper2";
        else backgroundNow = "whitepaper1";
    }
    void changeXrotation(){
        isRotate = isRotate^true;
    }
    void changeToPorcelain1(){textureNow = "porcelain1";}
    void changeToPorcelain2(){textureNow = "porcelain2";}
    void changeToWood1() {textureNow = "wood1";}
    void changeToWood2() {textureNow = "wood2";}
    void changeToStone1(){textureNow = "stone1";}
    void changeToStone2(){textureNow = "stone2";}
    void sample1(){QMessageBox::information(this,"DLC开发中","新版本择日上线，敬请期待!",QMessageBox::Yes);}
    void sample2(){preLoadPath(":/premodel/premodel/teacup.txt");}
    void sample3(){preLoadPath(":/premodel/premodel/teaboard.txt");}
    void sample4(){preLoadPath(":/premodel/premodel/stoneTable.txt");}
    void clearBoard();
    void load();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h){}
    void keyPressEvent(QKeyEvent *event);
protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

};

#endif // PAINTINGBOARD_H
