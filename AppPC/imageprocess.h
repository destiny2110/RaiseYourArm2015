#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <opencv2/opencv.hpp>
#include <cv.h>

#define TYPE_ROBOT 1
#define TYPE_GIFT 2

#define CALIB_OWN_ROBOT 2
#define CALIB_OP_ROBOT 4

class Object
{
public:
    int width,height;
    cv::Point center;
    double area;
    int type;
    Object();
    bool operator() (Object x, Object y)
    {
        return (x.center.y < y.center.y);
    }
};

class ImageProcess
{
public:
    int minArea,maxArea;
    int minRobot,maxRobot;
    int minGift,maxGift;
    int blurSize;
    cv::Mat frame,draw;
    ImageProcess();
    std::vector<cv::Point2f> corners;
    std::vector<Object> objectList;
    //std::vector<cv::RotatedRect> frameProcess();
    std::vector<cv::Point> frameProcess();
    void drawRotedRect(cv::RotatedRect rect);
    //std::vector<cv::RotatedRect> Find_All_Contours(cv::Mat threshold_frame, int area_min, int area_max);
    std::vector<cv::Point> Find_All_Contours(cv::Mat threshold_frame, int area_min, int area_max);
    std::vector<cv::Point> Find_Biggest_Contour(cv::Mat threshold_frame);
    std::vector<cv::Point> getWayPoints(std::vector<cv::RotatedRect> box, cv::Point center);
    void calAvgColor(cv::Mat InputImg,int AvgColor[3]);
    void RobotDistinguisher();
    int Robot2Cursor_Pointer;
    int Robot1Cursor_Pointer;
    //Cursor for robot 1
    std::vector<cv::Point> Robot1Cursor_Point;
    //Cursor for robot 2
    std::vector<cv::Point> Robot2Cursor_Point;
private:
    cv::Mat quad;
    std::vector<cv::Point2f> pts;
    //Stage dimensions
    int Stage_Height;//1.8mx1.8m
    int Stage_Width;
    std::vector<cv::Point> Cursor_Point;
    int Cursor_Pointer;

    int Robot1_Color[3];
    int Robot2_Color[3];
    int Calib_Flag;
    //Rotated rectangle for robot
    std::vector<cv::RotatedRect> RobotRR;
    std::vector<int> RobotRR_Area;
    std::vector<cv::Point> RobotRR_GP;

    //Rotated rectangle for gift
    std::vector<cv::RotatedRect> GiftRR;
    std::vector<int> GiftRR_Area;
    std::vector<cv::Point> GiftRR_GP;
};

#endif // IMAGEPROCESS_H
