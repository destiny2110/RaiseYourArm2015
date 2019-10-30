#include "imageprocess.h"

using namespace cv;
using namespace std;

Object::Object()
{
    center.x = 0;
    center.y = 0;
    width = 0;
    height = 0;
    type = 0;
    double area = 0;
}

ImageProcess::ImageProcess()
{
    minArea = 500;
    maxArea = 5000;
    minRobot = 0;
    maxRobot = 1200;
    minGift = 1200;
    maxGift = 5000;
    blurSize = 31;
    Stage_Height = 480;
    Stage_Width = 480;
    Cursor_Pointer = 0;
    Calib_Flag = 0;
    quad = Mat::zeros(480,640,CV_8UC3);
    pts.clear();
    pts.push_back(Point2f(0,0));
    pts.push_back(Point2f(639,0));
    pts.push_back(Point2f(639,479));
    pts.push_back(Point2f(0,479));
    corners.clear();
    corners.push_back(Point2f(0,0));
    corners.push_back(Point2f(639,0));
    corners.push_back(Point2f(639,479));
    corners.push_back(Point2f(0,479));
    objectList.clear();
}

void ImageProcess::drawRotedRect(RotatedRect rect)
{
    Point2f rect_points[4]; rect.points( rect_points );
    for( int j = 0; j < 4; j++ )
    {
       line( draw, rect_points[j], rect_points[(j+1)%4], Scalar(0,0,255), 1, 8 );
    }
}

//vector<RotatedRect> ImageProcess::frameProcess()
vector<Point> ImageProcess::frameProcess()
{

    objectList.clear();
    Mat _image,gray,athresimage;
    Mat transmtx = getPerspectiveTransform(corners, pts);
    warpPerspective(frame,quad,transmtx,quad.size());
    _image = quad.clone();
    draw = quad.clone();
    if (Calib_Flag == 1)
    {
        GaussianBlur(_image,_image,Size(blurSize,blurSize),0,0);
        cvtColor(_image,gray,CV_BGR2GRAY);
        adaptiveThreshold(gray, athresimage,255,ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY,51,-10);
        Mat ellipseStruct = getStructuringElement(MORPH_ELLIPSE, Size(7,7));
        morphologyEx(athresimage,athresimage,MORPH_GRADIENT,ellipseStruct);
        Find_All_Contours(athresimage,minArea,maxArea);
        RobotDistinguisher();
    }
    if (Calib_Flag == 0 && Robot1Cursor_Point.size()==2 && Robot2Cursor_Point.size()==2)
    {
        Rect Robot1Color_Area = Rect(Robot1Cursor_Point.at(0), Robot1Cursor_Point.at(1));
        Rect Robot2Color_Area = Rect(Robot2Cursor_Point.at(0), Robot2Cursor_Point.at(1));
    }
}

//vector<RotatedRect> ImageProcess::Find_All_Contours(Mat threshold_frame, int area_min, int area_max)
vector<Point> ImageProcess::Find_All_Contours(Mat threshold_frame, int area_min, int area_max)
{
    vector< vector<Point> > contours;//Vector for storing contour
    vector<Vec4i> hierarchy;
    vector<Point> Gravity_Points;
    Point x1,x2;
    Object object;
    double angle=0;
    //vector<RotatedRect> allcontours;
    RobotRR.clear();
    RobotRR_Area.clear();
    RobotRR_GP.clear();

    findContours(threshold_frame,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );//Find the contours in the image
    for(unsigned int i = 0; i < contours.size(); i++ ) // iterate through each contour.
    {
        double a=contourArea( contours[i],false);  //  Find the area of contour

        if(a>area_min && a<area_max)
        {
            //drawContours(quad2,contours,i,Scalar(0,0,255),2,8);
            //Rect boundingbox = boundingRect(contours[i]);
            //rectangle(quad2,boundingbox,Scalar(255,0,0),2);
            RotatedRect boundingbox = minAreaRect(contours[i]);
            Point2f rect_points[4];
            boundingbox.points(rect_points);

            Point2f gravitypoint=Point2f(0,0);
            RobotRR.push_back(boundingbox);
            RobotRR_Area.push_back(boundingbox.size.area());
            RobotRR_GP.push_back(gravitypoint);
            for(int j=0;j<4;j++)
            {
                //line(quad2,rect_points[j],rect_points[(j+1)%4],Scalar(0,0,255),2,8);
                gravitypoint.x = gravitypoint.x+rect_points[j].x;
                gravitypoint.y = gravitypoint.y+rect_points[j].y;
            }
            //allcontours.push_back(boundingbox);

            gravitypoint.x=gravitypoint.x/4;
            gravitypoint.y=gravitypoint.y/4;


            //char area[25];
            //sprintf(area,"%.2Find_All_Contours(athresimage,500,5000);lf", a);
            //putText(quad2, area, gravitypoint,FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
//            Vec4i thisVec = hierarchy.at(i);
//            if (thisVec[3]!=-1)
//            {
//                continue;
//            }
            if(a<maxRobot && a>minRobot)
            {
                RotatedRect box = minAreaRect(contours[i]);
                drawRotedRect(box);
                if (box.size.width < box.size.height) {
                  angle = 90 + box.angle;
                }
                else
                {
                  angle = box.angle;
                }
                angle = angle/180.0*CV_PI;
                x1.x = gravitypoint.x + 80*cos(angle);
                x1.y = gravitypoint.y + 80*sin(angle);
                x2.x = gravitypoint.x - 80*cos(angle);
                x2.y = gravitypoint.y - 80*sin(angle);
                line(draw,x1,x2,Scalar(255,0,0),1,LINE_AA);
                circle(draw,Point(int(gravitypoint.x),int(gravitypoint.y)),3,Scalar(0,0,255),-1);
                putText(draw, "ROBOT", gravitypoint,
                FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
                object.type = TYPE_ROBOT;
                object.area = a;
                object.center = gravitypoint;
                object.width = box.size.width;
                object.width = box.size.height;
                objectList.push_back(object);
            }
            else if (a<maxGift && a>minGift)
            {
                RotatedRect box = minAreaRect(contours[i]);
                drawRotedRect(box);
                circle(draw,Point(int(gravitypoint.x),int(gravitypoint.y)),3,Scalar(0,0,255),-1);
                putText(draw, "GIFT", gravitypoint,
                FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
                object.type = TYPE_ROBOT;
                object.area = a;
                object.center = gravitypoint;
                object.width = box.size.width;
                object.height = box.size.height;
                objectList.push_back(object);
            }

            Gravity_Points.push_back(gravitypoint);

        }
//        if(i==0)
//        {
//            drawContours(quad2,contours,i,Scalar(0,255,0),-1);
//        }
//        else drawContours(quad2,contours,i,Scalar(255,0,0),-1);
    }
    //return allcontours;


    //Rect boundingbox = boundingRect(contours[largest_contour_index]);

    //RotatedRect boundingbox = minAreaRect(contours[largest_contour_index]);
    //Point2f rect_points[4]; boundingbox.points(rect_points);
    //for(int i=0;i<4;i++) line(quad2,rect_points[i],rect_points[(i+1)%4],Scalar(0,255,0),1,8);

    return Gravity_Points;
}

vector<Point> ImageProcess::Find_Biggest_Contour(Mat threshold_frame)
{
    vector< vector<Point> > contours;//Vector for storing contour
    vector<Vec4i> hierarchy;
    int largest_area=0;
    int largest_contour_index=0;
    findContours(threshold_frame,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );//Find the contours in the image
    for(unsigned int i = 0; i < contours.size(); i++ ) // iterate through each contour.
    {
        double a=contourArea( contours[i],false);  //  Find the area of contour
        if(a>largest_area)
        {
            largest_area=a;
            largest_contour_index=i;                //Store the index of largest contour

            RotatedRect boundingbox = minAreaRect(contours[i]);
            Point2f rect_points[4]; boundingbox.points(rect_points);
            for(int j=0;j<4;j++)
            {
                line(quad,rect_points[j],rect_points[(j+1)%4],Scalar(0,255,0),2,8);
            }
        }
    }

    drawContours(quad,contours,largest_contour_index,Scalar(0,255,0),-1);
    //Rect boundingbox = boundingRect(contours[largest_contour_index]);
    //rectangle(quad2,boundingbox,Scalar(0,255,0),2);
    return contours[largest_contour_index];
}

void ImageProcess::calAvgColor(Mat InputImg,int AvgColor[3])
{
    vector<Mat> BGR_Channels;
    split(InputImg, BGR_Channels);

    AvgColor[0]=0;
    AvgColor[1]=0;
    AvgColor[2]=0;

    for(int i = 0; i<BGR_Channels[0].cols;i++)//width counter
    {
        for(int j = 0;j<BGR_Channels[0].rows;j++)//height counter
        {
            AvgColor[0] = AvgColor[0] + BGR_Channels[0].at<uchar>(i,j);//B
            AvgColor[1] = AvgColor[1] + BGR_Channels[1].at<uchar>(i,j);//G
            AvgColor[2] = AvgColor[2] + BGR_Channels[2].at<uchar>(i,j);//R
        }
    }

    int area=BGR_Channels[0].cols*BGR_Channels[0].rows;
    AvgColor[0] = AvgColor[0]/(area);
    AvgColor[1] = AvgColor[1]/(area);
    AvgColor[2] = AvgColor[2]/(area);
}

void ImageProcess::RobotDistinguisher()
{
    if(RobotRR.size()==2)
    {

        Rect robot1area = Rect(RobotRR_GP.at(0).x-10,RobotRR_GP.at(0).y-5,10,10);
        Rect robot2area = Rect(RobotRR_GP.at(1).x-10,RobotRR_GP.at(1).y-5,10,10);

        Mat robot1area_mat = quad(robot1area);
        Mat robot2area_mat = quad(robot2area);

        int robot1color[3];
        int robot2color[3];

        calAvgColor(robot1area_mat,robot1color);
        calAvgColor(robot2area_mat,robot2color);

        double ColorDif1_With1 = sqrt(pow(robot1color[0]-Robot1_Color[0],2)+pow(robot1color[1]-Robot1_Color[1],2)+pow(robot1color[2]-Robot1_Color[2],2));
        double ColorDif1_With2 = sqrt(pow(robot1color[0]-Robot2_Color[0],2)+pow(robot1color[1]-Robot2_Color[1],2)+pow(robot1color[2]-Robot2_Color[2],2));
        double ColorDif2_With1 = sqrt(pow(robot2color[0]-Robot1_Color[0],2)+pow(robot2color[1]-Robot1_Color[1],2)+pow(robot2color[2]-Robot1_Color[2],2));
        double ColorDif2_With2 = sqrt(pow(robot2color[0]-Robot2_Color[0],2)+pow(robot2color[1]-Robot2_Color[1],2)+pow(robot2color[2]-Robot2_Color[2],2));

        if( (ColorDif1_With1<ColorDif2_With1) && (ColorDif1_With2>ColorDif2_With2))
        {
            putText(draw, "ROBOT1", RobotRR_GP.at(0),
                    FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0,255,0), 1, CV_AA);
            putText(draw, "ROBOT2", RobotRR_GP.at(1),
                    FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0,255,0), 1, CV_AA);
        }
        else if( (ColorDif1_With1>ColorDif2_With1) && (ColorDif1_With2<ColorDif2_With2))
        {
            putText(draw, "ROBOT2", RobotRR_GP.at(0),
                    FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0,255,0), 1, CV_AA);
            putText(draw, "ROBOT1", RobotRR_GP.at(1),
                    FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0,255,0), 1, CV_AA);
        }
        else
        {
            putText(draw, "CAN NOT SEPERATE!!!", Point(20,20),
                    FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0,255,0), 1, CV_AA);
        }
    }
    else
    {
        putText(draw, "TOO MANY ROBOTS!!!", Point(20,20),
                FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0,255,0), 1, CV_AA);
    }
}
