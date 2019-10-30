#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "imageprocessing.h"
#include "hostcomm.h"
#include "mainwindow.h"
#include <qserialport.h>
using namespace cv;
using namespace std;

#define M_PI 3.14

ImageProcessing::ImageProcessing()
{
    serial = new QSerialPort;
    comm = new HostComm;
    en_gift_1 = true;
    en_gift_2 = false;
    en_gift_3 = false;
}

int ImageProcessing::count(int a)
{
    a+=1;
    return a;
}

cv::Mat ImageProcessing:: ImageGetCooor(cv::Mat input, int param1, int block_size, int kernelsize, int blursize,
                              int Hmin, int Hmax, int Smin, int Smax, int Vmin, int Vmax,
                              int R_min, int R_max, int G_min, int G_max, int Head_min, int Head_max ,
                              int RobotNum, int GiftNum, int Headnum,
                              int H_Hmin, int H_Hmax, int S_Hmin, int S_Hmax, int V_Hmin, int V_Hmax,
                              int goal, int gift1, int gift2, int gift3,
                              bool en_gift1, bool en_gift2, bool en_gift3)
{
    Mat Gray_Image,HSV_Image,Robot_Threshold,Gift_Threshold,kernel,Head_Threshold;

    namedWindow("Gift",WINDOW_AUTOSIZE);

    blur(input,input,Size(blursize,blursize),Point(-1,-1),BORDER_DEFAULT);
    cvtColor(input,Gray_Image,CV_BGR2GRAY);
    cvtColor(input,HSV_Image,CV_BGR2HSV);

    adaptiveThreshold(Gray_Image,Robot_Threshold,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,block_size*2+3,param1);

    inRange(HSV_Image,Scalar(Hmin,Smin,Vmin),Scalar(Hmax,Smax,Vmax),Gift_Threshold);
    inRange(HSV_Image,Scalar(H_Hmin,S_Hmin,V_Hmin),Scalar(H_Hmax,S_Hmax,V_Hmax),Head_Threshold);

    kernel = getStructuringElement(MORPH_RECT,Size(2*kernelsize+3,2*kernelsize+3),Point(1,1));
    erode(Robot_Threshold,Robot_Threshold,kernel,Point(1,1),1,BORDER_CONSTANT,morphologyDefaultBorderValue());
    dilate(Robot_Threshold,Robot_Threshold,kernel,Point(1,1),1,BORDER_CONSTANT,morphologyDefaultBorderValue());


    kernel = getStructuringElement(MORPH_RECT,Size(2*kernelsize+3,2*kernelsize+3),Point(1,1));
    erode(Gift_Threshold,Gift_Threshold,kernel,Point(1,1),1,BORDER_CONSTANT,morphologyDefaultBorderValue());
    dilate(Gift_Threshold,Gift_Threshold,kernel,Point(1,1),1,BORDER_CONSTANT,morphologyDefaultBorderValue());

    Mat Frame_Draw = input.clone();

    //-------------------------------------------ROBOT-------------------------------------------
    vector<vector<Point> > Robotcontours;    // moi contours la mot tap hop diem   --> nhieu diem -> vector
    vector<Vec4i>Robothierachi;
    Robotcontours.clear();
    Robothierachi.clear();
    Mat Robot_Threshold2 = Robot_Threshold.clone();
    findContours(Robot_Threshold2,Robotcontours,Robothierachi,CV_RETR_LIST,CV_CHAIN_APPROX_NONE,Point());
    int b = Robotcontours.size();
    Point Robot_center, Head_center, Gift_center;

    if (b<RobotNum)
    {
        for (unsigned int i = 0;i<b;i++)
        {
            //  ham tinh dien tich contour contourArea(...,...)
            RotatedRect rect = minAreaRect(Robotcontours.at(i)); // duong bao hinh chu nhat quanh no
            CvBox2D box = minAreaRect(Robotcontours.at(i));
            Point2f rect_point[4];
            rect.points(rect_point);
            int a = rect.size.area();
            if ((a>R_min) && (a<R_max))
            {
                Robot_Area = rect.size.area();
                Robot_center = box.center;
                R_x = box.center.x;
                R_y = box.center.y;
                R_h = box.size.height;
                R_w = box.size.width;
                R_angle = box.angle+90;

                //if (R_angle > 45)
                //{ R_angle -= 90;}


                drawContours(Frame_Draw,Robotcontours,i,Scalar(0,0,255),1,8);  // thickness = -1 la to nghuyen vung lun ^^
                for(unsigned int j=0; j<4; j++)
                {
                    circle(Frame_Draw, rect_point[j],3, Scalar(200, 255, 0), -1, 8);
                }
                circle(Frame_Draw, rect.center,3,Scalar(255,0,255),-1,8);
            }
        }
    }

    //-------------------------------------------HEAD--------------------------------------------
    vector<vector<Point> > Headcontours;    // moi contours la mot tap hop diem   --> nhieu diem -> vector
    vector<Vec4i>Headhierachi;
    Headcontours.clear();
    Headhierachi.clear();
    Mat Head_Threshold2 = Head_Threshold.clone();
    findContours(Head_Threshold2,Headcontours,Headhierachi,CV_RETR_LIST,CV_CHAIN_APPROX_NONE,Point());

    int c = Headcontours.size();
    if (c< Headnum)
    {
        for (unsigned int i = 0;i<Headcontours.size();i++)
        {
            //  ham tinh dien tich contour contourArea(...,...)
            RotatedRect rect = minAreaRect(Headcontours.at(i)); // duong bao hinh chu nhat quanh no
            CvBox2D box = minAreaRect(Headcontours.at(i));
            Point2f rect_point[4];
            rect.points(rect_point);
            int a = rect.size.area();
            if ((a>Head_min) && (a<Head_max))
            {
                Head_Area = rect.size.area();
                Head_center = box.center;
                H_x = box.center.x;
                H_y = box.center.y;
                H_h = box.size.height;
                H_w = box.size.width;
                H_angle = box.angle+90;
                drawContours(Frame_Draw,Headcontours,i,Scalar(100,255,125),1,8);  // thickness = -1 la to nghuyen vung lun ^^
                circle(Frame_Draw, rect.center,3,Scalar(255,0,25),-1,8);
            }
        }
    }



    //-------------------------------------------GIFT--------------------------------------------
    vector<vector<Point> > Giftcontours;    // moi contours la mot tap hop diem   --> nhieu diem -> vector
    vector<Vec4i>Gifthierachi;
    Giftcontours.clear();
    Gifthierachi.clear();
    Mat Gift_Threshold2 = Gift_Threshold.clone();
    findContours(Gift_Threshold2,Giftcontours,Gifthierachi,CV_RETR_LIST,CV_CHAIN_APPROX_NONE,Point());

    int p = Giftcontours.size();
    if (p<GiftNum)
    {
        for (unsigned int k = 0; k < p ;k++)
        {
            //  ham tinh dien tich contour contourArea(...,...)
            RotatedRect Grect = minAreaRect(Giftcontours.at(k)); // duong bao hinh chu nhat quanh no
            CvBox2D Gbox = minAreaRect(Giftcontours.at(k));
            Point2f Grect_point[4];
            Grect.points(Grect_point);
            int e = Grect.size.area();

            if ((e>G_min) && (e<G_max))
            {
                y_giftSelect = Gbox.center.y;

                if (en_gift1 || en_gift_1)
                {
                    if (y_giftSelect<gift1)
                        {
                            Gift_Area = Grect.size.area();
                            Gift_center = Gbox.center;
                            G_x = Gbox.center.x;
                            x_gift1 = G_x;
                            G_y = Gbox.center.y;
                            G_h = Gbox.size.height;
                            G_w = Gbox.size.width;
                            G_angle = Gbox.angle+90;
                            drawContours(Frame_Draw,Giftcontours,k,Scalar(0,0,255),1,8);  // thickness = -1 la to nghuyen vung lun ^^
                            for(unsigned int j=0; j<4; j++)
                            {
                                circle(Frame_Draw, Grect_point[j],3, Scalar(0, 255, 0), -1, 8);
                            }
                            circle(Frame_Draw, Grect.center,3,Scalar(0,0,255),-1,8);
                        }
                }

                if (en_gift2 || en_gift_2)
                {
                    if ((y_giftSelect>gift1)&&(y_giftSelect<gift2))
                        {
                            Gift_Area = Grect.size.area();
                            Gift_center = Gbox.center;
                            G_x = Gbox.center.x;
                            x_gift2 = G_x;
                            G_y = Gbox.center.y;
                            G_h = Gbox.size.height;
                            G_w = Gbox.size.width;
                            G_angle = Gbox.angle+90;
                            drawContours(Frame_Draw,Giftcontours,k,Scalar(0,0,255),1,8);  // thickness = -1 la to nghuyen vung lun ^^
                            for(unsigned int j=0; j<4; j++)
                            {
                                circle(Frame_Draw, Grect_point[j],3, Scalar(0, 255, 0), -1, 8);
                            }
                            circle(Frame_Draw, Grect.center,3,Scalar(0,0,255),-1,8);
                        }
                }

                if (en_gift3 || en_gift_3)
                {
                    if ((y_giftSelect>gift2)&&(y_giftSelect<gift3))
                        {
                            Gift_Area = Grect.size.area();
                            Gift_center = Gbox.center;
                            G_x = Gbox.center.x;
                            x_gift3 = G_x;
                            G_y = Gbox.center.y;
                            G_h = Gbox.size.height;
                            G_w = Gbox.size.width;
                            G_angle = Gbox.angle+90;
                            drawContours(Frame_Draw,Giftcontours,k,Scalar(0,0,255),1,8);  // thickness = -1 la to nghuyen vung lun ^^
                            for(unsigned int j=0; j<4; j++)
                            {
                                circle(Frame_Draw, Grect_point[j],3, Scalar(0, 255, 0), -1, 8);
                            }
                            circle(Frame_Draw, Grect.center,3,Scalar(0,0,255),-1,8);
                        }
                }

                if (x_gift1 >= goal)
                {
                    en_gift_1 = true;
                    en_gift_2 = false;
                    en_gift_3 = false;
                }
                else if (x_gift2 >= goal)
                {
                    en_gift_1 = false;
                    en_gift_2 = true;
                    en_gift_3 = false;
                }
                else if (x_gift3 >= goal)
                {
                    en_gift_1 = false;
                    en_gift_2 = false;
                    en_gift_3 = true;
                }
            }
        }
    }

    double x = sqrt(pow((G_x-R_x),2) + pow((G_y-R_y),2));
    double y = sqrt(pow((G_x-H_x),2) + pow((G_y-H_y),2));
    double z = sqrt(pow((H_x-R_x),2) + pow((H_y-R_y),2));
    angle = acos((pow(y,2)+pow(z,2)-pow(x,2))/(2*y*z));
    angle = angle*180/M_PI;

    imshow("Head",Head_Threshold);
    imshow("Gift",Gift_Threshold);
    imshow("Robot",Robot_Threshold);

    line(Frame_Draw,Head_center,Gift_center,Scalar(255,0,0),1,8,0);
    line(Frame_Draw,Head_center,Robot_center,Scalar(255,0,0),1,8,0);

    line(Frame_Draw,Point(goal,0),Point(goal,500),Scalar(0,0,255),1,8,0);
    line(Frame_Draw,Point(0,gift1),Point(500,gift1),Scalar(255,255,0),1,8,0);
    line(Frame_Draw,Point(0,gift2),Point(500,gift2),Scalar(0,255,255),1,8,0);
    line(Frame_Draw,Point(0,gift3),Point(500,gift3),Scalar(255,0,255),1,8,0);

    return Frame_Draw;
}


void ImageProcessing::sendData()
{
    HostComm *comm = new HostComm();
    QSerialPort *serial = new QSerialPort();

    //qDebug("gift (%d, %d) || Height %d || Width %d || Gift_area %d || Gift_angle %d ",G_x,G_y,G_h,G_w,Gift_Area,G_angle);
    //qDebug("robot (%d, %d) || Height %d || Width %d || Robot_area %d || Robot_angle %d",R_x,R_y,R_h,R_w,Robot_Area,R_angle);

    quint8 buffer[30];
    quint16 len;
    len = comm->prepareImgUpdate(buffer,R_angle, angle, R_x, R_y, G_x, G_y);
    serial->write((char*)buffer,len);
    serial->write("abc");
}
