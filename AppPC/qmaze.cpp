#include "qmaze.h"
#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QByteArray>
#include <QMouseEvent>
#include <QFont>
#include <QFileDialog>
#include "newmazedialog.h"

#define X_OFFSET 40//for numbering
#define Y_OFFSET 30
#define CELL_X 30
#define CELL_Y 30
#define WALL_X 7
#define WALL_Y 7
#define ROBOT_SIZE_H 14
#define ROBOT_SIZE_V 14

QMaze::QMaze(QWidget *parent,int r,int c) : QWidget(parent)
{

    setMazeSize(r,c);
    fillMazeOutline();
    robotDir = UP;
    robotX=0;
    robotY=0;
    //setMazeStatus(QMaze::MAZE_RUNNING);
}
void QMaze::fillMazeOutline()
{
    int i;
    for (i=0;i<row;i++)
    {
        setVerticalWall(0,i,1);
        setVerticalWall(col,i,1);
    }
    for (i=0;i<col;i++)
    {
        setHorizontalWall(i,0,1);
        setHorizontalWall(i,row,1);
    }
}

bool QMaze::setMazeSize(int r, int c)
{
    if ((r<=0)||(c<=0))
        return false;
    row = r;
    col = c;
    verticalWall = QByteArray(r*(c+1),0);
    horizontalWall = QByteArray(c*(r+1),0);
    return true;
}

void QMaze::setVerticalWall(int x,int y,char isWall)
{
    if ((x>=0)&&(x<=col)&&(y>=0)&&(y<row))
        verticalWall[x+y*(col+1)]=isWall;
}
void QMaze::setHorizontalWall(int x,int y,char isWall)
{
    if ((x>=0)&&(x<col)&&(y>=0)&&(y<=row))
        horizontalWall[x+y*col]=isWall;
}
void QMaze::revertVerticalWall(int x,int y)
{
    if ((x>=0)&&(x<=col)&&(y>=0)&&(y<row))
        verticalWall[x+y*(col+1)] = !verticalWall[x+y*(col+1)];
}
void QMaze::revertHorizontalWall(int x,int y)
{
    if ((x>=0)&&(x<col)&&(y>=0)&&(y<=row))
        horizontalWall[x+y*col] = !horizontalWall[x+y*col];
}
QSize QMaze::minimumSizeHint() const
{
    return QSize(width(),height());
}
//! [1]

//! [2]
QSize QMaze::sizeHint() const
{
    return QSize(width(),height());
}
void QMaze::mousePressEvent ( QMouseEvent * ev )
{
    //    if (getMazeStatus()!=QMaze::MAZE_RUNNING)
    //    {
    int x=ev->x()-X_OFFSET;
    int y=ev->y()-Y_OFFSET;
    int tempX=x/(CELL_X+WALL_X);
    int tempY=y/(CELL_Y+WALL_Y);
    x-=tempX*(CELL_X+WALL_X)+WALL_X;
    y-=tempY*(CELL_Y+WALL_Y)+WALL_Y;
    if (y<0)
        revertHorizontalWall(tempX,tempY);
    else if (x<0)
        revertVerticalWall(tempX,tempY);
    update();
    //    }
}
void QMaze::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    drawText(&painter);
    //painter.save();
    painter.translate(X_OFFSET,Y_OFFSET);
    drawMaze(&painter);
    drawRobot(&painter);

    //painter.restore();
}
void QMaze::drawMaze(QPainter* p)
{
    int i,j,x=0,y=0;
    int mh=getMazeHeight();
    int mw=getMazeWidth();
    p->setBrush(QBrush(Qt::blue));
    p->setPen(QPen(Qt::blue, 0, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    for (i=0;i<=col;i++)
    {
        p->drawLine(QPoint(x,0)
                    ,QPoint(x,mh));
        x+=WALL_X;
        p->drawLine(QPoint(x,0)
                    ,QPoint(x,mh));
        x+=CELL_X;
    }
    for (i=0;i<=row;i++)
    {
        p->drawLine(QPoint(0,y)
                    ,QPoint(mw,y));
        y+=WALL_Y;
        p->drawLine(QPoint(0,y)
                    ,QPoint(mw,y));
        y+=CELL_Y;
    }
    //draw outline
    //    p->drawRect(QRect(0,0,mw,WALL_Y));
    //    p->drawRect(QRect(0,WALL_Y,WALL_X,mh-2*WALL_Y));
    //    p->drawRect(QRect(0,mh-WALL_Y,mw,WALL_Y));
    //    p->drawRect(QRect(mw-WALL_X,WALL_Y,WALL_X,mh-2*WALL_Y));
    //draw wall
    for (i=0;i<row;i++)
    {
        for (j=0;j<col+1;j++)
        {
            if (verticalWall[i*(col+1)+j])
                p->drawRect(QRect(j*(WALL_X+CELL_X),i*(WALL_Y+CELL_Y),WALL_X,2*WALL_Y+CELL_Y));
        }
    }
    for (i=0;i<row+1;i++)
    {
        for (j=0;j<col;j++)
        {
            if (horizontalWall[i*col+j])
                p->drawRect(QRect(j*(WALL_X+CELL_X),i*(WALL_Y+CELL_Y),2*WALL_X+CELL_X,WALL_Y));
        }
    }
}
void QMaze::drawRobot(QPainter* p)
{
    int x=getRobotX();
    int y=getRow()-getRobotY()-1;
    if ((x<0)||(x>=getCol())||(y<0)||(y>=getRow()))
        return;
    p->save();
    p->setBrush(QBrush(Qt::green));
    p->setPen(QPen(Qt::green, 0, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    p->translate((CELL_X+WALL_X)*x+WALL_X+CELL_X/2,
                 (CELL_Y+WALL_Y)*y+WALL_Y+CELL_Y/2);

    QPainterPath path;

    path.moveTo(ROBOT_SIZE_H/2, ROBOT_SIZE_H/2);
    path.lineTo(ROBOT_SIZE_H/2,-ROBOT_SIZE_H/2);
    path.lineTo(-ROBOT_SIZE_H/2,-ROBOT_SIZE_H/2);
    path.lineTo(-ROBOT_SIZE_H/2,ROBOT_SIZE_H/2);
    path.arcTo(QRect(-ROBOT_SIZE_H/2,0,ROBOT_SIZE_V,ROBOT_SIZE_V),0.0,-180.0);

    p->rotate(90*static_cast<int>(robotDir));
    p->drawPath(path);
    p->restore();
}
void QMaze::drawText(QPainter* p)
{
    int i;
    p->setPen(QPen(Qt::blue, 0, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    p->setFont(QFont("Times", 10, QFont::Bold));
    for (i=0;i<row;i++)
        p->drawText(X_OFFSET/2-3,Y_OFFSET+i*(WALL_Y+CELL_Y)+WALL_Y+CELL_Y/2+5,QString::number(row-i-1));
    for (i=0;i<col;i++)
        p->drawText(X_OFFSET+i*(WALL_X+CELL_X)+WALL_X+CELL_X/2-3,Y_OFFSET/2+5,QString::number(i));
}

int QMaze::getRow()
{
    return row;
}
int QMaze::getCol()
{
    return col;
}
int QMaze::getMazeWidth()
{
    int c=getCol();
    return (c*CELL_X+(c+1)*WALL_X);
}
int QMaze::getMazeHeight()
{
    int r=getRow();
    return (r*CELL_Y+(r+1)*WALL_Y);
}
QMaze::MAZE_STATUS QMaze::getMazeStatus()
{
    return mazeStatus;
}

void QMaze::setMazeStatus(MAZE_STATUS ms)
{
    mazeStatus = ms;
}
void QMaze::setRobotPos(int x,int y)
{
    if ((robotX==x) && (robotY==y))
        return;

    if ((robotX<x)&&(robotX>=0))
        robotDir= RIGHT;
    else if (robotX>x)
        robotDir=LEFT;
    else if ((robotY<y)&&(robotY>=0))
        robotDir=UP;
    else if (robotY>y)
        robotDir=DOWN;

    robotX=x;
    robotY=y;
    update();
}
int QMaze::getRobotX()
{
    return robotX;
}
int QMaze::getRobotY()
{
    return robotY;
}

void QMaze::save()
{
    if (path.isEmpty())
        path = QFileDialog::getSaveFileName(this,"Save","","Maze file (*.mz)");
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return;
    QDataStream out(&file);
    out<<(qint32)row;
    out<<(qint32)col;
    int i;
    for (i=0;i<verticalWall.size();i++)
        out<<(qint8)verticalWall[i];
    for (i=0;i<horizontalWall.size();i++)
        out<<(qint8)horizontalWall[i];

    file.close();
}

void QMaze::saveAs()
{
    path.clear();
    save();
}

void QMaze::load()
{
    path = QFileDialog::getOpenFileName(this,"Open","","Maze files (*.mz)");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QDataStream in(&file);
    qint32 r, c;
    qint8 temp;
    in>>r;
    in>>c;
    setMazeSize(r,c);
    fillMazeOutline();
    for (r=0;r<verticalWall.size();r++)
    {
        in>>temp;
        verticalWall[r]=temp;
    }
    for (r=0;r<horizontalWall.size();r++)
    {
        in>>temp;
        horizontalWall[r]=temp;
    }
    update();
    file.close();
}
void QMaze::createNewMaze()
{
    NewMazeDialog *newDialog = new NewMazeDialog(this);
    if (newDialog->exec() == QDialog::Accepted)
        createNewMaze(newDialog->getRow(),newDialog->getCol());
}

void QMaze::createNewMaze(int r,int c)
{
    if (setMazeSize(r,c))
    {
        fillMazeOutline();
        update();
    }
}
