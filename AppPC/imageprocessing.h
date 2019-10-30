#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#include <opencv2/opencv.hpp>
#include <cv.h>
#include "hostcomm.h"
#include <qserialport.h>


// TODO: Add opencv code here
class ImageProcessing
{
public:
    ImageProcessing();
    int count(int a);
    cv :: Mat input;
    cv::Mat ImageGetCooor(cv::Mat input, int param1, int block_size, int kernelsize, int blursize,
                                  int Hmin, int Hmax, int Smin, int Smax, int Vmin, int Vmax,
                                  int R_min, int R_max, int G_min, int G_max, int Head_min, int Head_max ,
                                  int RobotNum, int GiftNum, int Headnum,
                                  int H_Hmin, int H_Hmax, int S_Hmin, int S_Hmax, int V_Hmin, int V_Hmax,
                                  int goal, int gift1, int gift2, int gift3,
                                  bool en_gift1, bool en_gift2, bool en_gift3);
    int R_x, R_y, G_x, G_y, G_h, G_w, R_h, R_w, G_angle, R_angle, Gift_Area, Robot_Area;
    int Head_Area, H_x, H_y, H_h, H_w, H_angle;
    int goal;
    int y_giftSelect;
    bool en_gift_1, en_gift_2, en_gift_3;
    int x_gift1, x_gift2, x_gift3;


    double angle;

public slots:
    void sendData();
private:
    QSerialPort *serial;
    HostComm *comm;
    int x_goal;

};

#endif // IMAGEPROCESSING_H
