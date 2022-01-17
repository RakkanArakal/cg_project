#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QObject>
#include <QSlider>

class MySlider : public QSlider
{
public:
    MySlider(QWidget *parent = nullptr);
    ~MySlider();

signals:
    void ValueChanged();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    bool m_bLButtonDown;

};

#endif // MYSLIDER_H
