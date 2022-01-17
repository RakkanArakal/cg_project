#include "component.h"
#include <QVector3D>
#include <math.h>
/******************* 1. Cube 立方体 ***********************/
Cube::Cube(): VBO(0){
    core = QOpenGLContext::currentContext()->functions();
}

Cube::~Cube(){
    if(VBO != 0)
        core->glDeleteBuffers(1, &VBO);
}

void Cube::init(){
    float vertices[] = {
        // positions        // textures        // normals
        //Back Face
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f, //bottom-left
        0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f, //top-right
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, -1.0f,

        //Front Face
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,

        //Left Face
        -0.5f,  0.5f,  0.5f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,

        //Right Face
        0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        //Bottom Face
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f,

        //Top Face
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    };
    core->glGenBuffers(1, &VBO);

    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

void Cube::drawLight(){
    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glEnableVertexAttribArray(0);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    core->glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::draw(){
    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glEnableVertexAttribArray(0);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    core->glEnableVertexAttribArray(1);
    core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    core->glDrawArrays(GL_TRIANGLES, 0, 36);
}

/******************* 2. Plane 立方体 ***********************/
Plane::Plane(): VBO(0){
    core = QOpenGLContext::currentContext()->functions();
}

Plane::~Plane(){
    if(VBO != 0)
        core->glDeleteBuffers(1, &VBO);
}

void Plane::init(int type){

    if(type == 0){
        float vertices[] = {
            // positions           // textures
            -4.0f,  -2.5f, -2.8f,  1.0f, 0.0f,
            4.0f,  -2.5f, -2.8f,  0.0f,  0.0f,
            4.0f,   2.5f, -2.8f,  0.0f,  1.0f,

            4.0f,   2.5f, -2.8f,  0.0f,  1.0f,
            -4.0f,   2.5f, -2.8f,  1.0f,  1.0f,
            -4.0f,  -2.5f, -2.8f,  1.0f,  0.0f,
        };
        core->glGenBuffers(1, &VBO);

        core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }else if(type == 1){
        float vertices[] = {
            // positions        // textures
            -25.0f,  -2.0f, -25.0f,   0.0f, 10.0f,
            25.0f,  -2.0f, -25.0f,  10.0f, 10.0f,
            25.0f,  -2.0f,  25.0f,  10.0f,  0.0f,

            25.0f,  -2.0f,  25.0f,  10.0f,  0.0f,
            -25.0f,  -2.0f,  25.0f,  0.0f,   0.0f,
            -25.0f,  -2.0f, -25.0f,  0.0f,  10.0f
        };
        core->glGenBuffers(1, &VBO);

        core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }
    else if(type == 2){
        float vertices[] = {
            // positions        // textures
            -1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f,  1.0f, -1.0f, 0.0f, 1.0f,

            1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
            -1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
        };
        core->glGenBuffers(1, &VBO);

        core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }


}
void Plane::draw(){
    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glEnableVertexAttribArray(0);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    core->glEnableVertexAttribArray(1);
    core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    core->glDrawArrays(GL_TRIANGLES, 0, 6);
}

/******************* 3. Coordinate 坐标***********************/
//Coordinate::Coordinate(): VBO(0){
//    core = QOpenGLContext::currentContext()->functions();
//}

//Coordinate::~Coordinate(){
//    if(VBO != 0)
//        core->glDeleteBuffers(1, &VBO);
//}

//void Coordinate::init(){

//    float vertices[] = {
//        // positions
//        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

//        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

//        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
//    };

//    core->glGenBuffers(1, &VBO);

//    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//}

//void Coordinate::draw(){

//    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);

//    core->glEnableVertexAttribArray(0);
//    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    core->glEnableVertexAttribArray(1);
//    core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

//    core->glDrawArrays(GL_LINES, 0, 6);
//}



/******************* 4. Line 线段 ***********************/
Line::Line(): VBO(0){
    core = QOpenGLContext::currentContext()->functions();
}

Line::~Line(){
    if(VBO != 0)
        core->glDeleteBuffers(1, &VBO);
}


void Line::init(QVector<QPoint> pt,int c){

    float vertices[pt.size()*6];
    float r,g,b;
    if(c == green){
        r = 100/255.0f;
        g = 197/255.0f;
        b = 192/255.0f;
    }
    if(c == blue){
        r = 46/255.0f;
        g = 134/255.0f;
        b = 193/255.0f;
    }

    for(int i=0;i<pt.size();i++){

        vertices[i*6+0] =  ((float)(pt[i].x()-640)*4.0f/1280);
        vertices[i*6+1] =  ((float)(pt[i].y()-400)*2.5f/-800);
        vertices[i*6+2] = 0.0f;
        vertices[i*6+3] = r;
        vertices[i*6+4] = g;
        vertices[i*6+5] = b;
    }

    core->glGenBuffers(1, &VBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

void Line::draw(int num){
    core->glEnableVertexAttribArray(0);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    core->glEnableVertexAttribArray(1);
    core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    core->glLineWidth(2.0f);
    core->glEnable(GL_LINE_SMOOTH);
    core->glDrawArrays(GL_LINE_STRIP, 0, num);
}
/******************* 5. Point 点 ***********************/
Point::Point(): VBO(0){
    core = QOpenGLContext::currentContext()->functions();
}

Point::~Point(){
    if(VBO != 0)
        core->glDeleteBuffers(1, &VBO);
}


void Point::init(QPoint pt){

    float vertices[]= {
        // positions                                                           //color
        ((float)(pt.x()-635)*4.0f/1280), -((float)(pt.y()-395)*2.5f/800), 0.0f,0.4f,0.4f,0.4f,

        ((float)(pt.x()-645)*4.0f/1280), -((float)(pt.y()-395)*2.5f/800), 0.0f,0.4f,0.4f,0.4f,

        ((float)(pt.x()-645)*4.0f/1280), -((float)(pt.y()-405)*2.5f/800), 0.0f,0.4f,0.4f,0.4f,

        ((float)(pt.x()-635)*4.0f/1280), -((float)(pt.y()-405)*2.5f/800), 0.0f,0.4f,0.4f,0.4f

    };
    core->glGenBuffers(1, &VBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

void Point::drawCtrlPoint(){
    core->glEnableVertexAttribArray(0);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    core->glEnableVertexAttribArray(1);
    core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

    core->glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

/******************* 6. Rotator 旋转体 ***********************/
Rotator::Rotator(): VBO(0){
    core = QOpenGLContext::currentContext()->functions();
}

Rotator::~Rotator(){
    if(VBO != 0)
        core->glDeleteBuffers(1, &VBO);
}
#define PI 3.14159265f
void Rotator::init(QVector<QPoint> pt){

    float vertices[pt.size()*10*36];

    QVector<QVector3D> vec_nor;

    float angleSpan = 10;
    for(float angle = 0; angle < 360; angle += angleSpan){

        for(int i=0;i<pt.size();i++){
            float round1 = ((float)(pt[i].x()-675)*4.0f/1280);
            float curRad = angle * PI / 180;
            float nextRad = (angle + angleSpan)* PI / 180;
            int rowNum = (int)(angle/10)*pt.size()*10;

            float x0 = round1 * cos(curRad);
            float y0 = ((float)(pt[i].y()-400)*2.5f/-800);
            float z0 = round1 * sin(curRad);

            float x1 = round1 * cos(nextRad);
            float y1 = y0;
            float z1 = round1 * sin(nextRad);

            vertices[i*10+rowNum+0] = x0;
            vertices[i*10+rowNum+1] = y0;
            vertices[i*10+rowNum+2] = z0;
            vertices[i*10+rowNum+3] = (360.0f-angle)/360  ;
            vertices[i*10+rowNum+4] = ((pt.size()-i)/(float)pt.size());

            vertices[i*10+rowNum+5] = x1;
            vertices[i*10+rowNum+6] = y1;
            vertices[i*10+rowNum+7] = z1;
            vertices[i*10+rowNum+8] = (350.0f-angle)/360  ;
            vertices[i*10+rowNum+9] = ((pt.size()-i)/(float)pt.size());

            if(i == 0 || i == pt.size()-1  ){
                vec_nor.push_back(QVector3D(round1 * cos(curRad), ((float)(pt[i].y()-400)*2.5f/-800), round1 * sin(curRad)));
                vec_nor.push_back(QVector3D(round1 * cos(nextRad), ((float)(pt[i].y()-400)*2.5f/-800), round1 * sin(nextRad)));
            }else{


                float round0 = ((float)(pt[i-1].x()-675)*4.0f/1280);
                float round2 = ((float)(pt[i+1].x()-675)*4.0f/1280);
                float preRad = (angle - angleSpan) * PI / 180;
                float nextNextRad = (angle + angleSpan*2)* PI / 180;

                float x01 = round0 * cos(curRad);
                float y01 = ((float)(pt[i-1].y()-400)*2.5f/-800);
                float z01 = round0 * sin(curRad);

                float x02 = round1 * cos(preRad);
                float y02 = ((float)(pt[i].y()-400)*2.5f/-800);
                float z02 = round1 * sin(preRad);

                float x03 = round2 * cos(curRad);
                float y03 = ((float)(pt[i+1].y()-400)*2.5f/-800);
                float z03 = round2 * sin(curRad);

                float x11 = round0 * cos(nextRad);
                float y11 = ((float)(pt[i-1].y()-400)*2.5f/-800);
                float z11 = round0 * sin(nextRad);

                float x12 = round1 * cos(nextNextRad);
                float y12 = ((float)(pt[i].y()-400)*2.5f/-800);
                float z12 = round1 * sin(nextNextRad);

                float x13 = round2 * cos(nextRad);
                float y13 = ((float)(pt[i+1].y()-400)*2.5f/-800);
                float z13 = round2 * sin(nextRad);


                QVector3D v01 = QVector3D(x0,y0,z0) - QVector3D(x01,y01,z01);
                QVector3D v02 = QVector3D(x0,y0,z0) - QVector3D(x02,y02,z02);
                QVector3D v03 = QVector3D(x0,y0,z0) - QVector3D(x03,y03,z03);
                QVector3D v04 = QVector3D(x0,y0,z0) - QVector3D(x1,y1,z1);

                QVector3D v05 = QVector3D::normal(v01,v02);
                v05 += QVector3D::normal(v02,v03);
                v05 += QVector3D::normal(v03,v04);
                v05 += QVector3D::normal(v04,v01);
                v05.normalize();


                QVector3D v11 = QVector3D(x1,y1,z1) - QVector3D(x11,y11,z11);
                QVector3D v12 = QVector3D(x1,y1,z1) - QVector3D(x12,y12,z12);
                QVector3D v13 = QVector3D(x1,y1,z1) - QVector3D(x13,y13,z13);
                QVector3D v14 = QVector3D(x1,y1,z1) - QVector3D(x0,y0,z0);

                QVector3D v15 = QVector3D::normal(v11,v12);
                v15 += QVector3D::normal(v12,v13);
                v15 += QVector3D::normal(v13,v14);
                v15 += QVector3D::normal(v14,v11);
                v15.normalize();

                vec_nor.push_back(v05*(-1));
                vec_nor.push_back(v15);
            }

        }
    }

    core->glGenBuffers(1, &VBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    core->glGenBuffers(1, &norVBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, norVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D) * vec_nor.size(), &vec_nor[0], GL_STATIC_DRAW);

}

void Rotator::draw(int num){

    num *= 72;
    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glEnableVertexAttribArray(0);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    core->glEnableVertexAttribArray(1);
    core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));

    core->glBindBuffer(GL_ARRAY_BUFFER, norVBO);
    core->glEnableVertexAttribArray(2);
    core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), (void*)0);



    core->glDrawArrays(GL_TRIANGLE_STRIP , 0, num);
}
