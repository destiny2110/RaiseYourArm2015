#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"
#include <QDateTime>
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QCameraInfo>
#include <QImage>
#include <QTime>

#include "imageprocessing.h"

using namespace cv;
using namespace std;

Q_DECLARE_METATYPE(QCameraInfo)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    calibflag = 0;
    console = new Console;
    serial = new QSerialPort(this);
    comm = new HostComm(this);
    serial->clear();
    settings = new SettingsDialog;
    about = new AboutUs;

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(true);
    ui->actionConfigure->setEnabled(true);
    ui->actionTerminal->setEnabled(true);
    ui->actionOpen->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionSaveAs->setEnabled(true);
    ui->actionNew->setEnabled(true);

    initActionsConnections();
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(ui->btnCapture,SIGNAL(clicked()),this, SLOT(toggleCapture()));
    connect(serial,SIGNAL(readyRead()),this,SLOT(serialReceive()));

    connect(ui->imgDisplay,SIGNAL(mousePress()),this,SLOT(def()));

    timer = new QTimer(this);
    timer->start(30);
    captureTimer = new QTimer(this);
    connect(captureTimer, SIGNAL(timeout()), this, SLOT(reCapture()));
    foreach (const QCameraInfo &cameraInfo, QCameraInfo::availableCameras()) {
        QStringList list;
        list<< cameraInfo.description()<<cameraInfo.deviceName();
        ui->cbbCamSelect->addItem(list.first(),list);
    }
//    cap = VideoCapture(0);
    connect(ui->btnSend,SIGNAL(clicked()),this,SLOT(send_data()));
    connect(ui->btnView,SIGNAL(clicked()),this,SLOT(view_data()));
    connect(ui->btn_resetCUT,SIGNAL(clicked()),this,SLOT(reset_CUT()));

    connect(ui->btn_debugPIC,SIGNAL(clicked()),this,SLOT(debug_Picture()));
    connect(ui->btn_pic1,SIGNAL(clicked()),this,SLOT(Picture1()));
    connect(ui->btn_pic2,SIGNAL(clicked()),this,SLOT(Picture2()));
    connect(ui->btn_pic3,SIGNAL(clicked()),this,SLOT(Picture3()));
    connect(ui->btn_pic4,SIGNAL(clicked()),this,SLOT(Picture4()));
    connect(ui->btn_pic5,SIGNAL(clicked()),this,SLOT(Picture5()));
    connect(ui->btn_pic6,SIGNAL(clicked()),this,SLOT(Picture6()));
    connect(ui->btn_pic7,SIGNAL(clicked()),this,SLOT(Picture7()));
    connect(ui->btn_pic8,SIGNAL(clicked()),this,SLOT(Picture8()));
    connect(ui->btn_pic9,SIGNAL(clicked()),this,SLOT(Picture9()));
    connect(ui->btn_pic10,SIGNAL(clicked()),this,SLOT(Picture10()));

    startCapture = false;
    img = new ImageProcessing;
    showMaximized();
    start_Send = false;
    start_View = false;
    calibflag = false;
    picture = 0;
    i = 0;
    debug_pic = false;
}

void MainWindow::def()
{
    i++;
    ui->i_label->setText(QString::number(i));
    c.push_back(Point(ui->imgDisplay->x,ui->imgDisplay->y));
    if (i==4)
    {
        calibflag = true;
        i=0;
    }
    else
        calibflag = false;
}

void MainWindow::toggleCapture()
{
    if (!startCapture)
    {
        startCapture = true;
        ui->btnCapture->setText("Stop capture");
        ui->cbbCamSelect->setEnabled(false);
        if (cap.isOpened())
        {
            cap.release();
        }
        cap = VideoCapture(ui->cbbCamSelect->currentIndex());
        captureTimer->start();
    }
    else
    {
        startCapture = false;
        ui->btnCapture->setText("Start capture");
        ui->cbbCamSelect->setEnabled(true);
        captureTimer->stop();
    }
}

void MainWindow::reCapture()
{
    Mat  _image;
    cap >> image;

    if (debug_pic)
    {
        if (picture==1)
        {
            image = imread("D:\\debut\\test1.jpg",IMREAD_COLOR);
        }
        if (picture==2)
        {
            image = imread("D:\\debut\\test2.jpg",IMREAD_COLOR);
        }
        if (picture==3)
        {
            image = imread("D:\\debut\\test3.jpg",IMREAD_COLOR);
        }
        if (picture==4)
        {
            image = imread("D:\\debut\\test4.jpg",IMREAD_COLOR);
        }
        if (picture==5)
        {
            image = imread("D:\\debut\\test5.jpg",IMREAD_COLOR);
        }
        if (picture==6)
        {
            image = imread("D:\\debut\\test6.jpg",IMREAD_COLOR);
        }
        if (picture==7)
        {
            image = imread("D:\\debut\\test7.jpg",IMREAD_COLOR);
        }
        if (picture==8)
        {
            image = imread("D:\\debut\\test8.jpg",IMREAD_COLOR);
        }
        if (picture==9)
        {
            image = imread("D:\\debut\\test9.jpg",IMREAD_COLOR);
        }
        if (picture==10)
        {
            image = imread("D:\\debut\\test10.jpg",IMREAD_COLOR);
        }
    }

if (calibflag == true)
{
    Mat quad = Mat::zeros(500,500,CV_8UC3);
    vector<Point> quad_pts;
    quad_pts.push_back(Point(0,0));
    quad_pts.push_back(Point(quad.cols,0));
    quad_pts.push_back(Point(quad.cols,quad.rows));
    quad_pts.push_back(Point(0,quad.rows));
    vector<Point2f> Cursor_Pointf,quad_ptsf;
    Mat(c).convertTo(Cursor_Pointf,Mat(Cursor_Pointf).type());
    Mat(quad_pts).convertTo(quad_ptsf,Mat(quad_ptsf).type());
    Mat transmtx = cv::getPerspectiveTransform(Cursor_Pointf,quad_ptsf);
    Mat dts2 = image.clone();
    Mat quad2 = Mat::zeros(500,500,CV_8UC3);
    warpPerspective(dts2,quad2,transmtx,quad.size());

    image = quad2;
}

_image = img->ImageGetCooor(image,ui->slider_param1->value(),ui->slider_blockSize->value(),ui->slider_kernelSize->value(),ui->slider_blur->value(),
                            ui->slider_Hmin->value(),ui->slider_Hmax->value(),ui->slider_Smin->value(),ui->slider_Smax->value(),ui->slider_Vmin->value(),ui->slider_Vmax->value(),
                            ui->slider_robotMinSize->value(),ui->slider_robotMaxSize->value(),ui->slider_giftminSize->value(),ui->slider_giftMaxSize->value(),ui->slider_HeadMinSize->value(),ui->slider_HeadMaxSize->value(),
                            ui->slider_RobotNum->value(),ui->slider_giftNum->value(),ui->slider_HeadNum->value(),
                            ui->slider_HHmin->value(),ui->slider_HHmax->value(),ui->slider_SHmin->value(),ui->slider_SHmax->value(),ui->slider_VHmin->value(),ui->slider_VHmax->value(),
                            ui->slider_goal->value(),ui->slider_gift_1->value(),ui->slider_gift_2->value(),ui->slider_gift_3->value(),
                            ui->check_gift1->isChecked(),ui->check_gift2->isChecked(),ui->check_gift3->isChecked());
    if (start_View)
    {
        ui->R_angle->setText(QString::number(img->R_angle));
        ui->R_x->setText(QString::number(img->R_x));
        ui->R_y->setText(QString::number(img->R_y));

        ui->G_x->setText(QString::number(img->G_x));
        ui->G_y->setText(QString::number(img->G_y));
        ui->G_angle->setText(QString::number(img->G_angle));

        ui->angle->setText(QString::number((int)img->angle));

        if (start_Send)
        {
            quint8 buffer[30];
            quint16 len;
            len = comm->prepareImgUpdate(buffer, (int)img->R_angle, img->angle , img->R_x, img->R_y, img->G_x, img->G_y);
            serial->write((char*)buffer,len);
        }

        int Rangle = img->R_angle;
        if (Rangle > 0)
        {
            ui->R_angle1->setText(QString::number(img->R_angle));
            ui->R_angle2->setText("nonVal");
        }
        if (Rangle < 0)
        {
            ui->R_angle1->setText("nonVal");
            ui->R_angle2->setText(QString::number(-(img->R_angle)));
        }


    }


    cvtColor(_image,_image,CV_BGR2RGB);
    QImage qImage = QImage((uchar*)_image.data,_image.cols,_image.rows,_image.step,QImage::Format_RGB888);
    ui->imgDisplay->setPixmap(QPixmap::fromImage(qImage));
}

MainWindow::~MainWindow()
{
    delete settings;
    delete console;
    delete ui;
}

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionTerminal, SIGNAL(triggered()),console,SLOT(show()));
    connect(comm, SIGNAL(recvData()),this,SLOT(recvPack()));
    connect(ui->actionAbout, SIGNAL(triggered()), about, SLOT(show()));
}

void MainWindow::recvPack()
{
//    int index = 0;
//    quint8 data[comm->hostGetLength()];
//    comm->hostGet(data);
//    switch (data[0]) {
//    case MSG_TRACK_BOT:
//        break;
//    case MSG_UPDATE_BOT:
//        break;
//    case MSG_START_TEST:
//        break;
//    default:
//        break;
//    }
}


// Slots
void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {

        console->setEnabled(true);
        console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
        ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                   .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                   .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }
}


void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWindow::readData()
{
    QByteArray array = serial->readAll();
    console->putData(array,array.size());
    int i;
    for (i=0;i<array.size();i++)
    {
        //inputData(array.at(i));
        comm->hostRecv(array.at(i));
    }
    serial->clear();
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::serialReceive()
{
    ui->txtReceive->setText(serial->readAll());
}

void MainWindow::send_data()
{
   if (start_Send==false)
   {
       start_Send = true;
       ui->btnSend->setText("STOP SEND");
   }
   else
   {
       start_Send = false;
       ui->btnSend->setText("START SEND");
   }
}
void MainWindow::view_data()
{
    if (start_View==false)
    {
        start_View = true;
        ui->btnView->setText("STOP VIEW");
    }
    else
    {
        start_View = false;
        ui->btnView->setText("START VIEW");
    }
}

void MainWindow::reset_CUT()
{
    i = 0;
    calibflag = false;
    c.clear();
    ui->i_label->setText(QString::number(i));
}

void MainWindow::debug_Picture()
{
    if (debug_pic == false)
    {
        debug_pic = true;
        ui->btn_debugPIC->setText("StopDebug");
    }
    else
    {
        debug_pic = false;
        ui->btn_debugPIC->setText("DebugPIC");
    }
}
void MainWindow::Picture1()
{
    picture = 1;
}
void MainWindow::Picture2()
{
    picture = 2;
}
void MainWindow::Picture3()
{
    picture = 3;
}
void MainWindow::Picture4()
{
    picture = 4;
}
void MainWindow::Picture5()
{
    picture = 5;
}
void MainWindow::Picture6()
{
    picture = 6;
}
void MainWindow::Picture7()
{
    picture = 7;
}
void MainWindow::Picture8()
{
    picture = 8;
}
void MainWindow::Picture9()
{
    picture = 9;
}
void MainWindow::Picture10()
{
    picture = 10;
}



