#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QQueue>
#include <QCamera>
#include "imageprocess.h"
#include "hostcomm.h"
#include "aboutus.h"
#include "imageprocessing.h"

namespace Ui {
class MainWindow;

}


class Console;
class SettingsDialog;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isConnected();
    void setConnected(bool b);
    cv::Mat image;
    std::vector<cv::Point> c;


private slots:
    void serialReceive();
    void openSerialPort();
    void closeSerialPort();
    void readData();
    void handleError(QSerialPort::SerialPortError error);
    void recvPack();
    void toggleCapture();
    void reCapture();
    void def();
    void send_data();
    void view_data();
    void reset_CUT();
    void debug_Picture();
    void Picture1();
    void Picture2();
    void Picture3();
    void Picture4();
    void Picture5();
    void Picture6();
    void Picture7();
    void Picture8();
    void Picture9();
    void Picture10();

private:
    void initActionsConnections();
    void process(char* array);
    void inputData(char c);
    void setupGraph();
    void toggleLock();
    void refreshCam();
    void setCamera(const QCameraInfo &cameraInfo);
    void updateBot(quint8 *data);
    Ui::MainWindow *ui;
    Console *console;
    SettingsDialog *settings;
    AboutUs *about;

    qint64 startTime;
    QTimer* timer;
    QTimer* captureTimer;
    cv::VideoCapture cap;
    bool startCapture;
    QQueue<double> graphQueue;
    QQueue<double> mazeQueue;

    QSerialPort *serial;
    HostComm *comm;
    ImageProcessing *img;
    qint32 vl,vr;
    bool calibflag;
    int i;
    bool start_Send;
    bool start_View;
    int picture;
    bool debug_pic;
};

#endif // MAINWINDOW_H
