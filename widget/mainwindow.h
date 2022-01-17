#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>
#include "paintingboard.h"
#include "renderScene.h"


class MainWindow : public QOpenGLWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPushButton *Painting ;
    QPushButton *Scene;
    QPushButton *Quit;

    QLabel *PaintingLabel;
    QLabel *SceneLabel;
    QLabel *QuitLabel;

    QFont ft;

    QTimer *timer;
    QMessageBox *QuitBox;

    PaintingBoard *paintboard;
    RenderScene *renderScene;
    Camera *camera ;
    Plane *plane ;

    void keyPressEvent(QKeyEvent *keyEvent);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h){}
    void keyReleaseEvent(QKeyEvent *event);
private slots:
    void ClickToScene();
    void ClickToQuit();
    void ClickToPainting();

};


#endif // MAINWINDOW_H
