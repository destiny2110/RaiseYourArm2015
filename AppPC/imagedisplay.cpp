#include <QToolTip>
#include <QString>
#include <QMouseEvent>

#include "imagedisplay.h"


ImageDisplay::ImageDisplay(QWidget *parent) : QLabel(parent)
{
    x=0;
    y=0;
}

ImageDisplay::~ImageDisplay()
{

}

void ImageDisplay::mouseMoveEvent(QMouseEvent *ev)
{
    QToolTip::showText(ev->globalPos(),
                       QString::number(ev->pos().x())+","+
                       QString::number(ev->pos().y()),
                       this,rect());
    //QLabel::mouseMoveEvent(ev);
}

void ImageDisplay::mousePressEvent(QMouseEvent *ev)
{
    this->x = ev->x();
    this->y = ev->y();
    emit mousePress();
}

void ImageDisplay::resetPoint()
{
    x=0;
    y=0;
}
