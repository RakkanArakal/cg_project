#include "renderScene.h"
#include <resourcemangager/resourcemanager.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QSlider>

const QVector3D LIGHT_POSITION(-30.0f, 30.0f, -60.0f);
RenderScene::RenderScene(QWidget *parent):
    QOpenGLWidget(parent){
    this->setGeometry(0, 0, 1280, 800);
    setFocusPolicy(Qt::StrongFocus);

    QSurfaceFormat newGLFormat = this->format();  //开启抗锯齿
    newGLFormat.setSamples(4);
    this->setFormat(newGLFormat);

    connect(&timer,SIGNAL(timeout()),this,SLOT(slotTimeout()));
    timer.start(10);

    mySlider = new MySlider(this);
    mySlider->setOrientation(Qt::Vertical);  // 垂直方向
    mySlider->setMinimum(0);  // 最小值
    mySlider->setMaximum(50);  // 最大值
    mySlider->setSingleStep(1);  // 步长
    mySlider->setGeometry(1230,610,20,120);
    mySlider->setValue(8);
    connect(mySlider, SIGNAL(valueChanged(int)),SLOT(setLightValue()));

    Load   = new QPushButton(this);
    Light  = new QPushButton(this);
    Flower = new QPushButton(this);
    Quit   = new QPushButton(this);
    Clear  = new QPushButton(this);
    model1 = new QPushButton(this);
    model2 = new QPushButton(this);
    model3 = new QPushButton(this);
    model4 = new QPushButton(this);
    model5 = new QPushButton(this);
    model6 = new QPushButton(this);
    model7 = new QPushButton(this);
    model8 = new QPushButton(this);
    mode   = new QPushButton(this);

    Light  ->setIconSize(QSize(60,60));
    Quit   ->setIconSize(QSize(60,60));
    Flower ->setIconSize(QSize(60,60));
    Load   ->setIconSize(QSize(60,60));
    Clear  ->setIconSize(QSize(60,60));
    model1 ->setIconSize(QSize(60,60));
    model2 ->setIconSize(QSize(60,60));
    model3 ->setIconSize(QSize(60,60));
    model4 ->setIconSize(QSize(60,60));
    model5 ->setIconSize(QSize(60,60));
    model6 ->setIconSize(QSize(60,60));
    model7 ->setIconSize(QSize(60,60));
    model8 ->setIconSize(QSize(60,60));
    mode   ->setIconSize(QSize(60,60));


    Light  ->setGeometry(1210,730,60,60);
    Quit   ->setGeometry(1210,10,60,60);
    Flower ->setGeometry(1140,730,60,60);
    Load   ->setGeometry(80,730,60,60);
    Clear  ->setGeometry(10,730,60,60);
    model1 ->setGeometry(10,650,60,60);
    model2 ->setGeometry(10,570,60,60);
    model3 ->setGeometry(10,490,60,60);
    model4 ->setGeometry(10,410,60,60);
    model5 ->setGeometry(10,330,60,60);
    model6 ->setGeometry(10,250,60,60);
    model7 ->setGeometry(10,170,60,60);
    model8 ->setGeometry(10,90,60,60);
    mode   ->setGeometry(10,10,60,60);

    model2 ->setDisabled(true);
    model3 ->setDisabled(true);
    model4 ->setDisabled(true);
    model5 ->setDisabled(true);
    model6 ->setDisabled(true);
    model7 ->setDisabled(true);
    model8 ->setDisabled(true);
    //    mode   ->setDisabled(true);

    Load  ->setFlat(1);
    Light ->setFlat(1);
    Quit  ->setFlat(1);
    Flower->setFlat(1);
    Clear ->setFlat(1);
    model1->setFlat(1);
    model2->setFlat(1);
    model3->setFlat(1);
    model4->setFlat(1);
    model5->setFlat(1);
    model6->setFlat(1);
    model7->setFlat(1);
    model8->setFlat(1);
    mode  ->setFlat(1);

    Load  ->setIcon(QIcon(":/imgs/image/icon/load2.png"));
    Light ->setIcon(QIcon(":/imgs/image/icon/Phong.png"));
    Quit  ->setIcon(QIcon(":/imgs/image/icon/quit2.png"));
    Flower->setIcon(QIcon(":/imgs/image/icon/flowericon.png"));
    Clear ->setIcon(QIcon(":/imgs/image/icon/clear2.png"));
    model1->setIcon(QIcon(":/imgs/image/icon/model1-1.png"));
    model2->setIcon(QIcon(":/imgs/image/icon/model2.png"));
    model3->setIcon(QIcon(":/imgs/image/icon/model3.png"));
    model4->setIcon(QIcon(":/imgs/image/icon/model4.png"));
    model5->setIcon(QIcon(":/imgs/image/icon/model5.png"));
    model6->setIcon(QIcon(":/imgs/image/icon/model6.png"));
    model7->setIcon(QIcon(":/imgs/image/icon/model7.png"));
    model8->setIcon(QIcon(":/imgs/image/icon/model8.png"));
    mode  ->setIcon(QIcon(":/imgs/image/icon/camera.png"));

    connect(Load,SIGNAL(clicked(bool)),SLOT(load()));
    connect(Quit,SIGNAL(clicked(bool)),SLOT(QuitPush()));
    connect(Light,SIGNAL(clicked(bool)),SLOT(changeLight()));
    connect(Clear,SIGNAL(clicked(bool)),SLOT(clear()));
    connect(Flower,SIGNAL(clicked(bool)),SLOT(flowersFalling()));
    connect(model1, &QPushButton::clicked, this, [=](){modelPush(1);} );
    connect(model2, &QPushButton::clicked, this, [=](){modelPush(2);} );
    connect(model3, &QPushButton::clicked, this, [=](){modelPush(3);} );
    connect(model4, &QPushButton::clicked, this, [=](){modelPush(4);} );
    connect(model5, &QPushButton::clicked, this, [=](){modelPush(5);} );
    connect(model6, &QPushButton::clicked, this, [=](){modelPush(6);} );
    connect(model7, &QPushButton::clicked, this, [=](){modelPush(7);} );
    connect(model8, &QPushButton::clicked, this, [=](){modelPush(8);} );

    bezier = new Bezier();
    modelMap.clear();
    buttonMap.clear();
    buttonMap[1] = model1;
    buttonMap[2] = model2;
    buttonMap[3] = model3;
    buttonMap[4] = model4;
    buttonMap[5] = model5;
    buttonMap[6] = model6;
    buttonMap[7] = model7;
    buttonMap[8] = model8;

    isCamera = true;
    isFalling = true;
    r_timer.start();
}

void RenderScene::clear(){

    for(auto iter = moveMap.end();; ){

        if(iter.value()){

            int num = iter.key();
            delete modelMap[num];
            modelMap.erase(modelMap.begin()+num-1);
            QString path =":/imgs/image/icon/model" + QString::number(num) +".png";
            buttonMap[num]->setIcon(QIcon(path));
            buttonMap[num]->setDisabled(true);

            iter = moveMap.erase(iter);
            continue;
        }
        if(iter == moveMap.begin())
            break;
        --iter;
    }
    isCamera = true;
    mode  ->setIcon(QIcon(":/imgs/image/icon/camera.png"));

}
void RenderScene::modelPush(int num){

    if(!buttonMap[num]->isEnabled()) return;
    if(moveMap[num]){
        QString path =":/imgs/image/icon/model" + QString::number(num) +"-1.png";
        buttonMap[num]->setIcon(QIcon(path));
        moveMap[num] = false;

        for(auto b:moveMap)
            if(b){
                isCamera = false;
                return;
            }

        isCamera = true;
        mode  ->setIcon(QIcon(":/imgs/image/icon/camera.png"));

    }
    else{

        QString path =":/imgs/image/icon/model" + QString::number(num) +"-2.png";
        buttonMap[num]->setIcon(QIcon(path));
        moveMap[num] = true;
        if(isCamera){
            isCamera = false;
            mode  ->setIcon(QIcon(":/imgs/image/icon/move.png"));
        }
    }
}

void RenderScene::load(){
    int num = modelMap.size()+1;
    if(num>8)
    {
        QMessageBox::information(NULL, "Error", "空间不足");
        return;
    }
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

    file.close();

    ResourceManager::loadShader(fileName, ":/shaders/shader/light_texture.vert", ":/shaders/shader/light_texture.frag");
    ResourceManager::getShader(fileName).use().setInteger("ambientMap", 0);
    ResourceManager::getShader(fileName).use().setVector3f("lightPos", LIGHT_POSITION);
    ResourceManager::getShader(fileName).use().setFloat("phongShininess", 8.0f);
    ResourceManager::getShader(fileName).use().setBool("isBlinn", isBlinn);

    num = 1;
    for(auto iter = moveMap.begin(); iter != moveMap.end(); ++iter){
        if(iter.key() != num){
            break;
        }
        num++;
    }

    modelMap[num] = new myModel(fileName,QVector3D(0,10.5,-60),8.0f,bezier_point,textureNow);
    QString path =":/imgs/image/icon/model" + QString::number(num) +"-1.png";
    buttonMap[num]->setEnabled(true);
    buttonMap[num]->setIcon(QIcon(path));
    moveMap  [num] = false;

}
RenderScene::~RenderScene(){
    if(camera)
        delete camera;
}
void RenderScene::setLightValue(){
    if(isBlinn){
        blinnShininess = (float)mySlider->value();
        ResourceManager::getShader("floor").use().setFloat("blinnShininess", blinnShininess);
        //        ResourceManager::getShader("table").use().setFloat("blinnShininess", blinnShininess);
    }else{
        phongShininess = (float)mySlider->value();
        ResourceManager::getShader("floor").use().setFloat("phongShininess", phongShininess);
        //        ResourceManager::getShader("table").use().setFloat("phongShininess", phongShininess);
    }

    for(auto m:modelMap){
        ResourceManager::getShader(m->name).use().setFloat("blinnShininess", blinnShininess);
        ResourceManager::getShader(m->name).use().setFloat("phongShininess", phongShininess);
    }


    this->update();
}

void RenderScene::changeLight(){
    if(isBlinn){
        Light ->setIcon(QIcon(":/imgs/image/icon/Phong.png"));
        mySlider->setValue(8);
        isBlinn = GL_FALSE;
    }else{
        Light ->setIcon(QIcon(":/imgs/image/icon/BPhong.png"));
        mySlider->setValue(32);
        isBlinn = GL_TRUE;
    }
    ResourceManager::getShader("floor").use().setBool("isBlinn", isBlinn);

    for(auto m:modelMap){
        ResourceManager::getShader(m->name).use().setBool("isBlinn", isBlinn);
    }

    setLightValue();
}

void RenderScene::setSkyBoxPath(int index){

    //    if(index == 1)
    //        skybox->setCubePath(":/skybox/skybox/1/right.jpg",
    //                            ":/skybox/skybox/1/top.jpg",
    //                            ":/skybox/skybox/1/front.jpg",
    //                            ":/skybox/skybox/1/left.jpg",
    //                            ":/skybox/skybox/1/bottom.jpg",
    //                            ":/skybox/skybox/1/back.jpg");
    //    else if (index == 2)
    skybox->setCubePath(":/skybox/skybox/2/right.jpg",
                        ":/skybox/skybox/2/top.jpg",
                        ":/skybox/skybox/2/front.jpg",
                        ":/skybox/skybox/2/left.jpg",
                        ":/skybox/skybox/2/bottom.jpg",
                        ":/skybox/skybox/2/back.jpg");
}
void RenderScene::initializeGL(){
    /*********** OGL核心 ***********/

    /*********** 键鼠响应及时间帧数操作  *************/
    for(GLuint i = 0; i != 1024; ++i) //初始化键盘按键
        keys[i] = GL_FALSE;

    isFirstMouse = GL_TRUE;
    isLeftMousePress = isBlinn = GL_FALSE;
    lastX = width() / 2.0f;
    lastY = height() / 2.0f;

    /************ 摄像机 ***********/
    camera = new Camera(QVector3D(0.0f, 0.0f, 3.0f));
    /*********** Light  *************/
//    light = new Cube();
//    light->init();
    light = new Rotator();
    clearBoard();
    point.push_back(QPoint(674,326));
    point.push_back(QPoint(820,326));
    point.push_back(QPoint(820,554));
    point.push_back(QPoint(674,554));
    light_point = bezier->bezier(point,4);
    /*********** Plane  *************/
    floor = new Plane();
    floor->init(1);

    /************** 天空盒 ************/
    skybox = new SkyBox();
    setSkyBoxPath(2);
    skybox->init();

    /***********  cube shader参数 **************/
    QMatrix4x4 model;
    model.scale(4.0f);
    model.translate(LIGHT_POSITION/4);
    ResourceManager::getShader("light").use().setMatrix4f("model", model);

    /***********  plane shader参数 **************/
    model.setToIdentity();
    model.scale(10.0f);
    ResourceManager::getShader("floor").use().setMatrix4f("model", model);
    ResourceManager::getShader("floor").use().setInteger("ambientMap", 0);
    ResourceManager::getShader("floor").use().setVector3f("lightPos", LIGHT_POSITION);
    ResourceManager::getShader("floor").use().setFloat("phongShininess",8.0f);
    ResourceManager::getShader("floor").use().setBool("isBlinn", isBlinn);

    preLoadPath(":/premodel/premodel/stoneTable.txt");

    for(int j=0;j<30;j++){
        for(int i=0;i<30;i++){

            QVector3D t = QVector3D(150-i*10,100,150-j*10);
            float dy = float(rand()%100/400.0f + 0.05f);
            Plane *flower = new Plane();
            flower->init(2);
            flowerMap[i+j*30] = new myFlower(t,dy,flower);

        }
    }

}


void RenderScene::paintGL(){

    QOpenGLFunctions *f = this->context()->functions();
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_BLEND);
    processInput(5);

    QMatrix4x4 projection, view;
    projection.perspective(camera->zoom, (GLfloat)width()/(GLfloat)height(), 0.1f, 2000.f);
    view = camera->getViewMatrix();

    /*********   灯  ************/
    ResourceManager::getShader("light").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("light").use().setMatrix4f("view", view);
    ResourceManager::getShader("light").use();
//    light->draw();
//    f->glActiveTexture(GL_TEXTURE0);
//    ResourceManager::getTexture("flower").bind();
    light->init(light_point);
    light->draw(150);
    /*********  地板 ************/
    ResourceManager::getShader("floor").use().setVector3f("viewPos", camera->position);
    ResourceManager::getShader("floor").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("floor").use().setMatrix4f("view", view);
    ResourceManager::getShader("floor").use();
    f->glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture("floor").bind();
    floor->draw();

    /********* 天空盒 ************/
    QMatrix4x4 skyboxView;
    skyboxView.setRow(0, QVector4D(view(0, 0), view(0, 1), view(0, 2), 0.0f));
    skyboxView.setRow(1, QVector4D(view(1, 0), view(1, 1), view(1, 2), 0.0f));
    skyboxView.setRow(2, QVector4D(view(2, 0), view(2, 1), view(2, 2), 0.0f));
    skyboxView.setRow(3, QVector4D(0.0f,       0.0f,       0.0f,       1.0f)); //这个去掉位移的4x4矩阵，使天空盒vertices的尺寸的改变，不再影响渲染效果
    ResourceManager::getShader("skybox").use().setMatrix4f("view", skyboxView);
    ResourceManager::getShader("skybox").use().setMatrix4f("projection", projection);
    f->glDepthFunc(GL_LEQUAL);
    ResourceManager::getShader("skybox").use();
    skybox->draw();
    f->glDepthFunc(GL_LESS);

    /*********  模型  ************/
    for(auto m:modelMap){
        QString name = m->name;
        ResourceManager::getShader(name).use().setVector3f("viewPos", camera->position);
        ResourceManager::getShader(name).use().setMatrix4f("projection", projection);
        ResourceManager::getShader(name).use().setMatrix4f("view", view);

        QMatrix4x4 model;
        model.translate(m->translation);
        model.scale(m->scale);
        ResourceManager::getShader(name).use().setMatrix4f("model", model);
        f->glActiveTexture(GL_TEXTURE0);
        ResourceManager::getTexture(m->textureNow).bind();

        Rotator *r = new Rotator();
        r->init(m->bezier_point);
        r->draw(m->bezier_point.size());
//        delete r;
    }
    /*********  落花  ************/
    if(isFalling)
    {
        ResourceManager::getShader("flower").use().setVector3f("viewPos", camera->position);
        ResourceManager::getShader("flower").use().setMatrix4f("projection", projection);
        ResourceManager::getShader("flower").use().setMatrix4f("view", view);
        f->glActiveTexture(GL_TEXTURE0);
        ResourceManager::getTexture("flower").bind();
        QMatrix4x4 model;

        for(auto myflower:flowerMap){
            QVector3D t = myflower->translation;
            float dy = myflower->dy;
            float y = t.y() - dy;
            if (y < - 10.0f) {
                myflower->dy = float(rand()%100/400.0f + 0.05f);
                y = 100.0f;
            }

            t.setY(y);
            myflower->translation = t;

            model.setToIdentity();
            model.translate(t);

            model.rotate(r_timer.elapsed()*(1.0f-dy)/10.0f,QVector3D(200.0f-y, 200.0f-y, 200.0f-y));
            ResourceManager::getShader("flower").use().setMatrix4f("model", model);
            myflower->flower->draw();
        }
    }

}


void RenderScene::clearBoard(){

    bezier_point.clear();
    point.clear();
    point_count = 0;
}


void RenderScene::preLoadPath(QString path){

    clearBoard();

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

    file.close();

    ResourceManager::loadShader(path, ":/shaders/shader/light_texture.vert", ":/shaders/shader/light_texture.frag");
    ResourceManager::getShader(path).use().setInteger("ambientMap", 0);
    ResourceManager::getShader(path).use().setVector3f("lightPos", LIGHT_POSITION);
    ResourceManager::getShader(path).use().setFloat("phongShininess", 8.0f);
    ResourceManager::getShader(path).use().setBool("isBlinn", isBlinn);

    int num = modelMap.size()+1;
    modelMap[num] = new myModel(path,QVector3D(0,-4.5,-60),15.0f,bezier_point,textureNow);
    moveMap [num] = false;
}



void RenderScene::processInput(GLfloat dt){


    if(isCamera){
        if (keys[Qt::Key_W])
            camera->processKeyboard(FORWARD, dt);
        if (keys[Qt::Key_S])
            camera->processKeyboard(BACKWARD, dt);
        if (keys[Qt::Key_A])
            camera->processKeyboard(LEFT, dt);
        if (keys[Qt::Key_D])
            camera->processKeyboard(RIGHT, dt);
        if (keys[Qt::Key_E])
            camera->processKeyboard(UP, dt);
        if (keys[Qt::Key_Q])
            camera->processKeyboard(DOWN, dt);
    }
    else{
        QVector3D trans(0.0f,0.0f,0.0f);
        if (keys[Qt::Key_W])
            trans += QVector3D(0,0,-1);
        if (keys[Qt::Key_S])
            trans += QVector3D(0,0, 1);
        if (keys[Qt::Key_A])
            trans += QVector3D(-1,0,0);
        if (keys[Qt::Key_D])
            trans += QVector3D(1,0,0);
        if (keys[Qt::Key_E])
            trans += QVector3D(0,1,0);
        if (keys[Qt::Key_Q])
            trans += QVector3D(0,-1,0);

        for(auto iter = moveMap.begin(); iter != moveMap.end(); ++iter){
            if(iter.value()){
                modelMap[iter.key()]->translation += trans*0.1f;
            }
        }
    }
}

void RenderScene::wheelEvent(QWheelEvent *event){
    QPoint offset = event->angleDelta();
    qDebug() << offset;
    if(isCamera){
        camera->processMouseScroll(offset.y()/20.0f);

    }
    else{
        for(auto iter = moveMap.begin(); iter != moveMap.end(); ++iter){
            if(iter.value()){
                modelMap[iter.key()]->scale += offset.y()/200.0f;
            }
        }
    }
}

void RenderScene::keyPressEvent(QKeyEvent *event){
    GLuint key = event->key();
    if(key >= 0 && key <= 1024)
        this->keys[key] = GL_TRUE;

    switch(key){
    case Qt::Key_Escape : QuitPush();
        break;
    case Qt::Key_R : load();
        break;
    case Qt::Key_F : flowersFalling();
        break;
    case Qt::Key_C : clear();
        break;
    case Qt::Key_L : changeLight();
        break;
    case Qt::Key_1 : modelPush(1);
        break;
    case Qt::Key_2 : modelPush(2);
        break;
    case Qt::Key_3 : modelPush(3);
        break;
    case Qt::Key_4 : modelPush(4);
        break;
    case Qt::Key_5 : modelPush(5);
        break;
    case Qt::Key_6 : modelPush(6);
        break;
    case Qt::Key_7 : modelPush(7);
        break;
    case Qt::Key_8 : modelPush(8);
        break;
    default:
        return;
    }


}
void RenderScene::keyReleaseEvent(QKeyEvent *event){
    GLuint key = event->key();
    if(key >= 0 && key <= 1024)
        this->keys[key] = GL_FALSE;
}

void RenderScene::mouseMoveEvent(QMouseEvent *event){
    GLint xpos = event->pos().x();
    GLint ypos = event->pos().y();
    if(isLeftMousePress){
        if (isFirstMouse){
            lastX = xpos;
            lastY = ypos;
            isFirstMouse = GL_FALSE;
        }
        GLint xoffset = xpos - lastX;
        GLint yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;
        camera->processMouseMovement(xoffset, yoffset);
    }
}

void RenderScene::mousePressEvent(QMouseEvent *event){

    if(event->button() == Qt::LeftButton)
        isLeftMousePress = GL_TRUE;
}

void RenderScene::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        isLeftMousePress = GL_FALSE;
        isFirstMouse = GL_TRUE;
    }
}


