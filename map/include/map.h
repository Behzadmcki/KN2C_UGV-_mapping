#ifndef OPTICALFLOWLK_H
#define OPTICALFLOWLK_H
#ifndef Q_MOC_RUN
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <geometry_msgs/PoseArray.h>
#include <std_msgs/String.h>
#include <hector_nav_msgs/GetNormal.h>
#include <hector_map_tools/HectorMapTools.h>
#include <hector_nav_msgs/GetRobotTrajectory.h>

#include <QObject>
#include <QByteArray>
#include <QImage>

#endif
#include <QUdpSocket>
#define feature_init_threshold 10
#define MAX_COUNT     20
#define winSize       cv::Size(31,31)
#define subPixWinSize cv::Size(1024,1024)

#define DRAW
#define pirint




#define yawLS 5
#define yawHS 3.5

#define xLS 100
#define xHS 20

using namespace cv;
using namespace std;
using namespace ros;

class map2im : public QObject
{

    Q_OBJECT
public:
    explicit map2im(QObject *parent = 0);

    Mat mapshow=Mat::zeros(1024,1024,CV_8UC3);
    void Map_subscriber_CB(const nav_msgs::OccupancyGrid &msg);
    void trajectory_subscriber_CB(const nav_msgs::Path &msg);
    void slam_out_pos_subscriber_CB(const geometry_msgs::PoseStamped &msg);

private:
    std::vector<uchar> mapReadyTOSendBuff;
    QByteArray img_data;
    nav_msgs::Path savedTrajectory;
    geometry_msgs::PoseStamped now_pos;
    QUdpSocket *sendMapSoket;
    QHostAddress *IP;
    std::vector<int> compressParam;
    Point a1,a2;
    nav_msgs::OccupancyGrid map;
    //XNetwork data_map;
    void doSomeThing(Mat b);
    QByteArray victimStatus;
    QUdpSocket* _socket;
    QByteArray resive_data_reg;
private slots:
    void data_resive();
};

#endif // OPTICALFLOWLK_H
