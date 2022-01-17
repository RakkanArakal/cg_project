#include "paintingboard.h"
#include <math.h>
#include <QVector>
#include <QPainter>
#include <QDir>

#include <QDateTime>
#include <QFileDialog>
#include <resourcemangager/resourcemanager.h>
using namespace std;

PaintingBoard::PaintingBoard(QWidget* parent):
    QOpenGLWidget (parent){

    QSurfaceFormat newGLFormat = this->format();  //开启抗锯齿
    newGLFormat.setSamples(8);
    this->setFormat(newGLFormat);

    Save  = new QPushButton(this);
    Load  = new QPushButton(this);
    Clear = new QPushButton(this);
    Quit  = new QPushButton(this);

    SaveL   = new QLabel(this);
    LoadL   = new QLabel(this);
    ClearL  = new QLabel(this);
    QuitL   = new QLabel(this);

    Save ->setIconSize(QSize(78,78));
    Load ->setIconSize(QSize(78,78));
    Clear->setIconSize(QSize(78,78));
    Quit ->setIconSize(QSize(78,78));

    Save ->setGeometry(394,102,78,78);
    Load ->setGeometry(394,15,78,78);
    Clear->setGeometry(164,102,78,78);
    Quit ->setGeometry(164,15,78,78);

    Save -> setFlat(1);
    Load -> setFlat(1);
    Clear -> setFlat(1);
    Quit  -> setFlat(1);

    Save->setIcon(QIcon(":/imgs/image/icon/save.png"));
    Load->setIcon(QIcon(":/imgs/image/icon/load.png"));
    Clear->setIcon(QIcon(":/imgs/image/icon/clear.png"));
    Quit->setIcon(QIcon(":/imgs/image/icon/quit1.png"));

    ft.setFamily("微软雅黑");
    ft.setPointSize(20);
    ft.setBold(1);

    SaveL -> setText("保存模型:");
    SaveL -> setFont(ft);
    SaveL -> setGeometry(277,102,120,78);
    SaveL -> setStyleSheet("color:rgb(102, 102, 102);");

    LoadL -> setText("载入模型:");
    LoadL -> setFont(ft);
    LoadL -> setGeometry(277,15,120,78);
    LoadL -> setStyleSheet("color:rgb(102, 102, 102);");

    ClearL -> setText("清除画布:");
    ClearL -> setFont(ft);
    ClearL -> setGeometry(46,102,120,78);
    ClearL -> setStyleSheet("color:rgb(102, 102, 102);");

    QuitL  -> setText("返回菜单:");
    QuitL  -> setFont(ft);
    QuitL  -> setGeometry(46,15,120,78);
    QuitL  -> setStyleSheet("color:rgb(102, 102, 102);");

    connect(Save  ,SIGNAL(clicked(bool)),this,SLOT(save()));
    connect(Load  ,SIGNAL(clicked(bool)),this,SLOT(load()));
    connect(Clear ,SIGNAL(clicked(bool)),this,SLOT(clearBoard()));
    connect(Quit  ,SIGNAL(clicked(bool)),this,SLOT(QuitPush()));


    QPushButton* sample1  = new QPushButton(this);
    QPushButton* sample2  = new QPushButton(this);
    QPushButton* sample3  = new QPushButton(this);
    QPushButton* sample4  = new QPushButton(this);

    sample1->setIconSize(QSize(182,166));
    sample2->setIconSize(QSize(182,166));
    sample3->setIconSize(QSize(182,166));
    sample4->setIconSize(QSize(182,166));

    sample1->setGeometry(486,14,182 ,166);
    sample2->setGeometry(683,14,182,166);
    sample3->setGeometry(881,14,182,166);
    sample4->setGeometry(1079,14,182,166);

    sample1->setFlat(1);
    sample2->setFlat(1);
    sample3->setFlat(1);
    sample4->setFlat(1);
//    sample1->setText("我是一个很长很长很长的文本");

    connect(sample1,SIGNAL(clicked(bool)),SLOT(sample1()));
    connect(sample2,SIGNAL(clicked(bool)),SLOT(sample2()));
    connect(sample3,SIGNAL(clicked(bool)),SLOT(sample3()));
    connect(sample4,SIGNAL(clicked(bool)),SLOT(sample4()));


    backgroundTex = new QPushButton(this);
    x_rotation    = new QPushButton(this);
    porcelainTex1 = new QPushButton(this);
    porcelainTex2 = new QPushButton(this);
    woodTex1      = new QPushButton(this);
    woodTex2      = new QPushButton(this);
    stoneTex1     = new QPushButton(this);
    stoneTex2     = new QPushButton(this);

    backgroundTex->setIconSize(QSize(60,60));
    x_rotation   ->setIconSize(QSize(60,60));
    porcelainTex1->setIconSize(QSize(45,45));
    porcelainTex2->setIconSize(QSize(45,45));
    woodTex1     ->setIconSize(QSize(45,45));
    woodTex2     ->setIconSize(QSize(45,45));
    stoneTex1    ->setIconSize(QSize(45,45));
    stoneTex2    ->setIconSize(QSize(45,45));


    backgroundTex->setGeometry(405,735,60,60);
    x_rotation   ->setGeometry(340,735,60,60);
    porcelainTex1->setGeometry(46,215,45,45);
    porcelainTex2->setGeometry(93,215,45,45);
    woodTex1     ->setGeometry(46,263,45,45);
    woodTex2     ->setGeometry(93,263,45,45);
    stoneTex1    ->setGeometry(46,311,45,45);
    stoneTex2    ->setGeometry(93,311,45,45);

    backgroundTex->setIcon(QIcon(":/imgs/image/icon/change.png"));
    x_rotation    ->setIcon(QIcon(":/imgs/image/icon/x_rotation.png"));
    porcelainTex1->setIcon(QIcon(":/imgs/image/icon/porcelain1icon.png"));
    porcelainTex2->setIcon(QIcon(":/imgs/image/icon/porcelain2icon.png"));
    woodTex1     ->setIcon(QIcon(":/imgs/image/icon/wood1icon.png"));
    woodTex2     ->setIcon(QIcon(":/imgs/image/icon/wood2icon.png"));
    stoneTex1    ->setIcon(QIcon(":/imgs/image/icon/stone1icon.png"));
    stoneTex2    ->setIcon(QIcon(":/imgs/image/icon/stone2icon.png"));


    backgroundTex->setFlat(1);
    x_rotation   ->setFlat(1);
    porcelainTex1->setFlat(1);
    porcelainTex2->setFlat(1);
    woodTex1     ->setFlat(1);
    woodTex2     ->setFlat(1);
    stoneTex1    ->setFlat(1);
    stoneTex2    ->setFlat(1);

    connect(backgroundTex,SIGNAL(clicked(bool)),SLOT(changeBackground()));
    connect(x_rotation,   SIGNAL(clicked(bool)),SLOT(changeXrotation()));
    connect(porcelainTex1,SIGNAL(clicked(bool)),SLOT(changeToPorcelain1()));
    connect(porcelainTex2,SIGNAL(clicked(bool)),SLOT(changeToPorcelain2()));
    connect(woodTex1,SIGNAL(clicked(bool)),SLOT(changeToWood1()));
    connect(woodTex2,SIGNAL(clicked(bool)),SLOT(changeToWood2()));
    connect(stoneTex1,SIGNAL(clicked(bool)),SLOT(changeToStone1()));
    connect(stoneTex2,SIGNAL(clicked(bool)),SLOT(changeToStone2()));

    resize(1280,800);
    connect(&time,SIGNAL(timeout()),this,SLOT(slotTimeout()));
    time.start(10);
    setFocusPolicy(Qt::StrongFocus);

    point_count = now = rotate_time = 0;
    right_move = isCtrl = false;
    isRotate = true;
    textureNow = "porcelain1";
    backgroundNow = "whitepaper1";
    bezier = new Bezier();
    preMap.clear();
}




void PaintingBoard::clearBoard(){

    bezier_point.clear();
    point.clear();
    point_count = 0;
}

void PaintingBoard::load(){
    QString fileName = QFileDialog::getOpenFileName(this,"Load","./model/","Text(*.txt)");

    QFile file(fileName);
    QString str;
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))                            //文件读取
    {
        QMessageBox::information(NULL, "Error", "The file failed to open");
        return;
    }
    clearBoard();
    QTextStream readStream(&file);
    str = readStream.readLine();
    textureNow = str;
    while(!readStream.atEnd())
    {
        str = readStream.readLine();
        QStringList strList = str.split(" ");
        if(strList.size()!=2)
            break;
        point.push_back(QPoint(strList[0].toInt(),strList[1].toInt()));
        point_count++;
    }
    bezier_point = bezier->bezier(point,point_count);


}
void PaintingBoard::save(){

    if(point_count < 3){
        QMessageBox::warning(this,"Error","没有模型可以保存！",QMessageBox::Yes);
        return;
    }
    QDir *DataFile = new QDir;
    bool exist = DataFile->exists("./model");
    if(!exist)
    {
        bool isok = DataFile->mkdir("./model"); // 新建文件夹
        if(!isok)
            QMessageBox::warning(this,"Error","can't mkdir",QMessageBox::Yes);
    }


    QString fileName = QFileDialog::getSaveFileName(this,"Save","./model/","Text(*.txt)");
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
    {
        QMessageBox::warning(this,"Error","保存失败！",QMessageBox::Yes);
        return;
    }
    QTextStream stream(&file);
    stream << textureNow << "\n";

    for(auto p:point){
        stream << p.x()  << " " << p.y() << "\n";
    }
    file.close();
    QMessageBox::information(this,"OK！","模型保存成功!",QMessageBox::Yes);

}
void PaintingBoard::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p1;
    int x, y;
    p1 = event->pos();

    x = p1.x();
    y = p1.y();



    if (right_move == true)
    {
        qDebug() << "x:" << p1.x() << " y:" << p1.y();
        if(y<200) {
            QCursor::setPos(this->mapToGlobal(QPoint(x, 200)));
        }
        if(y>785) {
            QCursor::setPos(this->mapToGlobal(QPoint(x, 785)));
        }
        if(x<490) {
            QCursor::setPos(this->mapToGlobal(QPoint(490, y)));
        }
        if(x>1255) {
            QCursor::setPos(this->mapToGlobal(QPoint(1255, y)));
        }

        now = point_count - 1;
        point[now].setX(x);
        point[now].setY(y);

    }
    else if(point.empty())
    {
        return;
    }
    else
    {
        if (now == 0)
        {
            for (int i = 0; i < point_count; i++)
            {
                if (x > point[i].x() - 10 && x < point[i].x() + 10
                        && y > point[i].y() - 10 && y < point[i].y() + 10)
                {
                    now = i;
                    break;
                }
            }
        }

        if (isCtrl || x > point[now].x() - 10 && x < point[now].x() + 10
                && y > point[now].y() - 10 && y < point[now].y() + 10)
        {
            isCtrl = true;

            qDebug() << "x:" << p1.x() << " y:" << p1.y();
            if(y<200) {
                QCursor::setPos(this->mapToGlobal(QPoint(x, 200)));
            }
            if(y>785) {
                QCursor::setPos(this->mapToGlobal(QPoint(x, 785)));
            }
            if(x<490) {
                QCursor::setPos(this->mapToGlobal(QPoint(490, y)));
            }
            if(x>1255) {
                QCursor::setPos(this->mapToGlobal(QPoint(1255, y)));
            }

            point[now].setX(x);
            point[now].setY(y);
        }
    }
    if (point_count > 2)
    {
        bezier_point = bezier->bezier(point,point_count);
    }
    update();
}
void PaintingBoard::mouseReleaseEvent(QMouseEvent *event)
{
    now = 0;
    right_move = isCtrl = false;
}

void PaintingBoard::mousePressEvent(QMouseEvent *event)
{



    if (event->button() == Qt::RightButton)
    {

        Pt = event->pos();
        //        qDebug() << "x:" << Pt.x() << " y:" << Pt.y();
        if(Pt.y()<210) return;
        if(Pt.x()<490) return;
        right_move = true;
        point.push_back(Pt);
        point_count++;
        if (point_count > 2)
        {
            bezier_point = bezier->bezier(point,point_count);
        }
        update();
    }
    else if (event->button() == Qt::LeftButton)
    {
        update();
    }
    else if (event->button() == Qt::MidButton)
    {
        if (point_count > 0)
        {
            --point_count;
            point.pop_back();
            bezier_point = bezier->bezier(point,point_count);
            update();
        }
    }
}

PaintingBoard::~PaintingBoard(){}

void PaintingBoard::initializeGL()
{

    ResourceManager::getShader("plane").use().setInteger("ambientMap", 0);
    QMatrix4x4 model;

    ResourceManager::getShader("line").use().setMatrix4f("model", model);
    ResourceManager::getShader("point").use().setMatrix4f("model", model);
    ResourceManager::getShader("plane").use().setMatrix4f("model", model);

    camera = new Camera(QVector3D(0.0f, 0.0f, 3.0f));
    plane = new Plane();
    plane->init(0);

    ctrlPoint = new Point();
    line    = new Line();
    rotator = new Rotator();

    pre_timer = new QElapsedTimer;
    pre_timer->start();

    QOpenGLFunctions *f = this->context()->functions();
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_BLEND);
    //    f->glEnable(GL_MULTISAMPLE);
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    QMatrix4x4 projection, view;
    projection.perspective(camera->zoom, (GLfloat)width()/(GLfloat)height(), 0.1f, 2000.f);
    view = camera->getViewMatrix();

    ResourceManager::getShader("rotator").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("rotator").use().setMatrix4f("view", view);
    ResourceManager::getShader("plane").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("plane").use().setMatrix4f("view", view);
    ResourceManager::getShader("line").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("line").use().setMatrix4f("view", view);
    ResourceManager::getShader("point").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("point").use().setMatrix4f("view", view);
    ResourceManager::getShader("premodel").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("premodel").use().setMatrix4f("view", view);


    unicorn = new Model();
    unicorn->init(":/premodel/premodel/unicorn.obj");
    ResourceManager::getShader("unicorn").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("unicorn").use().setMatrix4f("view", view);

    preLoadModel();


}

void PaintingBoard::paintGL()
{
    QOpenGLFunctions *f = this->context()->functions();

    preLoadModel();

    ResourceManager::getShader("plane").use();
    f->glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture(backgroundNow).bind();
    plane->draw();

    ResourceManager::getShader("point").use();
    for (int i = 0; i < point_count; i++)
    {
        ctrlPoint->init(point[i]);
        ctrlPoint->drawCtrlPoint();
    }

    ResourceManager::getShader("line").use();
    if (point_count == 2){
        line->init(point,green);
        line->draw(point.size());
    }

    if (point_count > 2)
    {
        line->init(bezier_point,blue);
        line->draw(bezier_point.size());
        line->init(point,green);
        line->draw(point.size());

        QMatrix4x4 model;
        model.scale(0.35f);
        model.translate(-3.5,-1.0,0);

        model.rotate(rotate_time, QVector3D(1.0f, 0.0f, 0.0f));

        ResourceManager::getShader("rotator").use().setMatrix4f("model", model);
        f->glActiveTexture(GL_TEXTURE0);

        ResourceManager::getTexture(textureNow).bind();

        rotator->init(bezier_point);
        rotator->draw(bezier_point.size());

    }




}
void PaintingBoard::preLoadPath(QString path){

    clearBoard();
    if(preMap.count(path)){
        textureNow = preMap[path].textureNow;
        point = preMap[path].point;
        point_count = preMap[path].point_count;
        bezier_point = bezier->bezier(point,point_count);
    }
    else{
        QFile file(path);
        QString str;
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            return;
        QTextStream readStream(&file);
        str = readStream.readLine();
        textureNow = str;
        while(!readStream.atEnd())
        {
            str = readStream.readLine();
            QStringList strList = str.split(" ");
            point.push_back(QPoint(strList[0].toInt(),strList[1].toInt()));
            point_count++;
        }
        bezier_point = bezier->bezier(point,point_count);
        preMap[path].point = point;
        preMap[path].point_count = point_count;
        preMap[path].textureNow = textureNow;
        file.close();
    }
}
void PaintingBoard::preLoadModel(){

    pointTmp = point;
    bezierTmp = bezier_point;
    cnt = point_count;
    textureTmp = textureNow;

    QOpenGLFunctions *f = this->context()->functions();

    QMatrix4x4 model;
    model.scale(0.15f);
    model.translate(10.9,6.2,0);
    model.rotate(45.0f, QVector3D(1.0f, 1.0f, 1.0f));
    model.rotate(pre_timer->elapsed() / 100.0f, QVector3D(0.0f, 1.0f, 0.0f));
    ResourceManager::getShader("premodel").use().setMatrix4f("model", model);
    preLoadPath(":/premodel/premodel/stoneTable.txt");
    f->glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture(textureNow).bind();
    Rotator* premodel4 = new Rotator();
    premodel4->init(bezier_point);
    premodel4->draw(bezier_point.size());

    model.setToIdentity();
    model.scale(0.18f);
    model.translate(5.6,5.3,0);
    model.rotate(70.0f, QVector3D(1.0f, 1.0f, 1.0f));
    model.rotate(pre_timer->elapsed() / 100.0f, QVector3D(0.0f, 1.0f, 0.0f));
    ResourceManager::getShader("premodel").use().setMatrix4f("model", model);
    preLoadPath(":/premodel/premodel/teaboard.txt");
    f->glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture(textureNow).bind();
    Rotator* premodel3 = new Rotator();
    premodel3->init(bezier_point);
    premodel3->draw(bezier_point.size());

    model.setToIdentity();
    model.scale(0.30f);
    model.translate(1.4,3.2,0);
    model.rotate(75.0f, QVector3D(1.0f, 1.0f, 0.5f));
    model.rotate(pre_timer->elapsed() / 100.0f, QVector3D(0.0f, 1.0f, 0.0f));
    ResourceManager::getShader("premodel").use().setMatrix4f("model", model);
    preLoadPath(":/premodel/premodel/teacup.txt");
    f->glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture(textureNow).bind();
    Rotator* premodel2 = new Rotator();
    premodel2->init(bezier_point);
    premodel2->draw(bezier_point.size());


    model.setToIdentity();
    model.scale(0.0020f);
    model.translate(-100.0f,510.0f,0);
    model.rotate(300.0f, QVector3D(1.0f, 0.0f, 0.0f));
    model.rotate(pre_timer->elapsed() / 80.0f, QVector3D(0.0f, 0.0f,1.0f));
    ResourceManager::getShader("unicorn").use().setMatrix4f("model", model);
    unicorn->draw(GL_TRUE);

    textureNow = textureTmp;
    point = pointTmp;
    bezier_point = bezierTmp;
    point_count = cnt;
}



void PaintingBoard::keyPressEvent(QKeyEvent *event){
    GLuint key = event->key();
    if(key == Qt::Key_Escape){
        QuitPush();
    }
    if(key == Qt::Key_Space){
        changeXrotation();
    }

}
