#include "mainwindow.h"

#include <QDialog>
#include <QPushButton>
#include <QTimer>

#include <resourcemangager/resourcemanager.h>


MainWindow::~MainWindow()
{
    //    delete this;
}


MainWindow::MainWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{

    setWindowTitle(tr("cg_516150910044"));      //decide the title of the welcome window
    resize(1280,800);
    this->setFixedSize(this->size());

    //    QPalette palette(this->palette());
    //    palette.setBrush(QPalette::Background,QPixmap(":/imgs/image/background1.jpg").scaled(this->size()));     //Set background picture of Gamemenu
    //    this->setPalette(palette);

    Painting  = new QPushButton(this);
    Scene     = new QPushButton(this);
    Quit      = new QPushButton(this);

    PaintingLabel = new QLabel(this);
    QuitLabel     = new QLabel(this);
    SceneLabel    = new QLabel(this);

    //Set the text
    PaintingLabel-> setText("加载画布:");
    SceneLabel   -> setText("场景渲染:");
    QuitLabel    -> setText("退出游戏:");


    ft.setFamily("微软雅黑");
    ft.setPointSize(20);
    ft.setBold(1);

    PaintingLabel->setStyleSheet("color:rgb(102, 102, 102);"); //Set the color of label
    SceneLabel->setStyleSheet("color:rgb(102, 102, 102);");
    QuitLabel->setStyleSheet("color:rgb(102, 102, 102);");

    PaintingLabel->setFont(ft);                    //Set the font of label
    SceneLabel->setFont(ft);
    QuitLabel->setFont(ft);


    //Set the position of label
    PaintingLabel->setGeometry(1045,550,125,80);
    SceneLabel   ->setGeometry(1045,630,150,80);
    QuitLabel    ->setGeometry(1045,710,125,80);

     //Set the size of icons
    Painting ->setIconSize(QSize(80,80));
    Scene    ->setIconSize(QSize(80,80));
    Quit     ->setIconSize(QSize(80,80));

      //Set the point of icons
    Painting  ->setGeometry(1170,550,80,80);
    Scene     ->setGeometry(1170,630,80,80);
    Quit      ->setGeometry(1170,710,80,80);

    Painting  ->setIcon(QIcon(":/imgs/image/icon/paint.png"));   //Set the picture of icons
    Scene     ->setIcon(QIcon(":/imgs/image/icon/scene.png"));
    Quit      ->setIcon(QIcon(":/imgs/image/icon/quit.png"));

    Painting  ->setFlat(1); //make icon invisible
    Scene     ->setFlat(1);
    Quit      ->setFlat(1);



    connect(Painting,SIGNAL(clicked(bool)),SLOT(ClickToPainting())); //connect the icons with particular functions
    connect(Scene,SIGNAL(clicked(bool)),SLOT(ClickToScene()));
    connect(Quit,SIGNAL(clicked(bool)),SLOT(ClickToQuit()));

    //    m_layout = new QVBoxLayout(this);
    //    setLayout(m_layout);
    setFocusPolicy(Qt::NoFocus);
    clearFocus();

    Scene->installEventFilter(this);
    Quit->installEventFilter(this);

}


void MainWindow::ClickToPainting(){
    this->clearFocus();

    paintboard = new PaintingBoard(this);
    paintboard->show();
}


void MainWindow::ClickToScene(){
    this->clearFocus();

    renderScene = new RenderScene(this);
    renderScene->show();

}

void MainWindow::ClickToQuit(){
    if(QMessageBox::Yes==QMessageBox::question(this,"Tips:","Leave the game?",QMessageBox::Yes|QMessageBox::No)){
        delete this;
        exit(0);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){
    //  oglManager->handleKeyReleaseEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent){
    switch (keyEvent->key()){
    case Qt::Key_Escape:
        ClickToQuit();
        return;
    default:
        break;

    }
}



void MainWindow::initializeGL()
{
    /************ 载入shader ***********/
    ResourceManager::loadShader("background", ":/shaders/shader/texture.vert", ":/shaders/shader/texture.frag");
    // board
    ResourceManager::loadShader("rotator", ":/shaders/shader/texture.vert", ":/shaders/shader/texture.frag");
    ResourceManager::loadShader("plane", ":/shaders/shader/texture.vert", ":/shaders/shader/texture.frag");
    ResourceManager::loadShader("line", ":/shaders/shader/color.vert", ":/shaders/shader/color.frag");
    ResourceManager::loadShader("point", ":/shaders/shader/color.vert", ":/shaders/shader/color.frag");
    ResourceManager::loadShader("premodel", ":/shaders/shader/texture.vert", ":/shaders/shader/texture.frag");

    // Scene
    ResourceManager::loadShader("floor", ":/shaders/shader/light_texture.vert", ":/shaders/shader/light_texture.frag");
    ResourceManager::loadShader("skybox", ":/shaders/shader/skybox.vert", ":/shaders/shader/skybox.frag");
//    ResourceManager::loadShader("light", ":/shaders/shader/flower.vert", ":/shaders/shader/flower.frag");
    ResourceManager::loadShader("light", ":/shaders/shader/light.vert", ":/shaders/shader/light.frag");
    ResourceManager::loadShader("flower", ":/shaders/shader/flower.vert", ":/shaders/shader/flower.frag");
    ResourceManager::loadShader("unicorn", ":/shaders/shader/unicorn.vert", ":/shaders/shader/unicorn.frag");
    /************ 载入Texture ***********/
    ResourceManager::loadTexture("background1", ":/imgs/image/background1.jpg");
    // board
    ResourceManager::loadTexture("porcelain1", ":/imgs/image/porcelain1.png");
    ResourceManager::loadTexture("porcelain2", ":/imgs/image/porcelain2.png");
    ResourceManager::loadTexture("wood1", ":/imgs/image/wood1.jpg");
    ResourceManager::loadTexture("wood2", ":/imgs/image/wood2.jpg");
    ResourceManager::loadTexture("stone1", ":/imgs/image/stone1.png");
    ResourceManager::loadTexture("stone2", ":/imgs/image/stone2.png");
    ResourceManager::loadTexture("whitepaper1", ":/imgs/image/whitepaper.png");
    ResourceManager::loadTexture("whitepaper2", ":/imgs/image/whitepaper.jpg");
    // Scene
    ResourceManager::loadTexture("brickwall", ":/skybox/skybox/2/bottom.jpg");
    ResourceManager::loadTexture("floor", ":/imgs/image/floor.jpg");
    ResourceManager::loadTexture("flower", ":/imgs/image/icon/flower.png");

    QMatrix4x4 model;
    ResourceManager::getShader("background").use().setMatrix4f("model", model);
    ResourceManager::getShader("background").use().setInteger("ambientMap", 0);

    camera = new Camera(QVector3D(0.0f, 0.0f, 3.0f));
    plane = new Plane();
    plane->init(0);

    QOpenGLFunctions *f = this->context()->functions();
    QMatrix4x4 projection, view;
    projection.perspective(camera->zoom, (GLfloat)width()/(GLfloat)height(), 0.1f, 2000.f);
    view = camera->getViewMatrix();

    ResourceManager::getShader("background").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("background").use().setMatrix4f("view", view);
}

void MainWindow::paintGL(){
    QOpenGLFunctions *f = this->context()->functions();

    ResourceManager::getShader("background").use();
    f->glActiveTexture(GL_TEXTURE0);
    ResourceManager::getTexture("background1").bind();
    plane->draw();

}
