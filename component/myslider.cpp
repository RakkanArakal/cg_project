#include "myslider.h"
#include <QMouseEvent>
#include <QDebug>

MySlider::MySlider(QWidget *parent):QSlider (parent)
{

}

MySlider::~MySlider()
{

}

void MySlider::mousePressEvent(QMouseEvent *ev)
{
    //获取当前点击位置
    int currentY = ev->pos().y();

    //获取当前点击的位置占整个Slider的百分比
    double per = currentY *1.0 /this->height();

    //利用算得的百分比得到具体数字
    int value = (1-per)*(this->maximum() - this->minimum()) + this->minimum();

    qDebug() << value;

    //设定滑动条位置
    this->setValue(value);

    //滑动条移动事件等事件也用到了mousePressEvent,加这句话是为了不对其产生影响，是的Slider能正常相应其他鼠标事件
    QSlider::mousePressEvent(ev);
}
void MySlider::mouseReleaseEvent(QMouseEvent *ev)
{
    QSlider::mouseReleaseEvent(ev);
    qDebug() << this->value();
//        emit ValueChanged();
}
