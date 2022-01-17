#ifndef LITTLETHINGS_H
#define LITTLETHINGS_H

#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QPoint>
/*
  这个类存储了一些 小玩意，为这些单独小玩意单独建类又好麻烦
  目前这些小玩意有：
  1.cube立方体
  2.plane平面
  3.Coordinate坐标系
*/
enum color
{
    blue,
    green,
};
/************* 1. Cube立方体 ******************/

class Cube{
public:
    Cube();
    ~Cube();
    void init();
    void draw();
    void drawLight();
private:
    QOpenGLFunctions *core;
    GLuint VBO;
};

/************* 2. plane二维平面 ******************/

class Plane{
public:
    Plane();
    ~Plane();
    void init(int type);
    void draw();
    void drawFloor();
private:
    QOpenGLFunctions *core;
    GLuint VBO;
};

/************ 3. 坐标类，一个简单的显示xyz坐标的类**************/
//class Coordinate{
//public:
//    Coordinate();
//    ~Coordinate();
//    void init();
//    void draw();
//private:
//    QOpenGLFunctions *core;
//    GLuint VBO;
//};

/************ 4. Line 线类       **************/
class Line{
public:
    Line();
    ~Line();
    void init();
    void draw();
    void init(QVector<QPoint> pt, int c);
    void draw(int num);
private:
    QOpenGLFunctions *core;
    GLuint VBO;
};

/************ 5. Point 控制顶点       **************/
class Point{
public:

    Point();
    ~Point();
    void drawCtrlPoint();
    void draw(int num);
    void init(QPoint pt);
    //    void init(QVector<QPoint> pt,int c);
private:
    QOpenGLFunctions *core;
    GLuint VBO;
};

/************ 6. Rotator 旋转体  **************/
class Rotator{
public:

    Rotator();
    ~Rotator();
    //    void init(QPoint pt);
    void init(QVector<QPoint> pt);
    void draw(int num);
private:
    QOpenGLFunctions *core;
    GLuint VBO;
    GLuint norVBO;
};



#endif // LITTLETHINGS_H
