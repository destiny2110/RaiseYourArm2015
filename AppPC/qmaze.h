#ifndef QMAZE_H
#define QMAZE_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

class QMaze : public QWidget
{
    Q_OBJECT

public:
    enum MAZE_STATUS{
        MAZE_RUNNING,
        MAZE_PAUSE,
        MAZE_STOP
    };
    enum ROBOT_DIR{
        UP=2,
        RIGHT=1,
        DOWN=0,
        LEFT=3
    };
    QMaze(QWidget *parent = 0,int r=15, int c=7);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    MAZE_STATUS getMazeStatus();
    void setMazeStatus(MAZE_STATUS ms);
    void setRobotPos(qint32 x,qint32 y);
    int getRobotX();
    int getRobotY();
    int getRow();
    int getCol();
    int setRow(int r);
    int setCol(int c);
    int getMazeWidth();
    int getMazeHeight();

signals:

public slots:
//    void run();
//    void stop();
//    void pause();
    void save();
    void saveAs();
    void load();
    void createNewMaze();
    void createNewMaze(int r, int c);
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent ( QMouseEvent * ev ) Q_DECL_OVERRIDE;
private:
    void drawMaze(QPainter* p);
    void drawRobot(QPainter* p);
    void drawText(QPainter* p);
//    void setPen(const QPen &pen);
//    void setBrush(const QBrush &brush);
private:
    int row,col;
    QByteArray verticalWall;
    QByteArray horizontalWall;
    int robotX,robotY;
    QString path;
    MAZE_STATUS mazeStatus;
    ROBOT_DIR robotDir;

    void setVerticalWall(int x,int y,char isWall);
    void setHorizontalWall(int x,int y,char isWall);
    void revertVerticalWall(int x,int y);
    void revertHorizontalWall(int x,int y);
    bool setMazeSize(int row, int col);
    void fillMazeOutline();

//    QPen pen;
//    QBrush brush;
};

#endif // QMAZE_H
