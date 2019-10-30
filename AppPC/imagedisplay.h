#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QWidget>
#include <QLabel>

class ImageDisplay : public QLabel
{
    Q_OBJECT
public:
    explicit ImageDisplay(QWidget *parent = 0); 
    ~ImageDisplay();
    int x;
    int y;
    void resetPoint();

signals:
    void mousePress();

public slots:

protected slots:
    virtual void mouseMoveEvent(QMouseEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);
};

#endif // IMAGEDISPLAY_H
