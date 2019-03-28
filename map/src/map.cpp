#include "map.h"

map2im::map2im(QObject *parent) : QObject(parent)
{
    IP=new QHostAddress("192.168.1.152");
    sendMapSoket=new QUdpSocket(this);
//cap.open(0);
    ROS_INFO("dastan");



   // _socket=new QUdpSocket(this);
    sendMapSoket->bind(QHostAddress::Any,8585);
    QObject::connect(sendMapSoket,SIGNAL(readyRead()),this,SLOT(data_resive()));

//    data_map.Set_serverIP("192.168.1.91",3131);
//    data_map.Set_clientIP("192.168.1.152",3232);


    compressParam.push_back(CV_IMWRITE_JPEG_QUALITY);
    compressParam.push_back(30);

}
int flag=0;
void map2im::Map_subscriber_CB(const nav_msgs::OccupancyGrid & msg){


    for(int i=0;i<1024*1024;i++)
    {



        if(msg.data.at(i)==0)
        {
            mapshow.at<Vec3b>(i)[0]=255;
             mapshow.at<Vec3b>(i)[1]=255;
              mapshow.at<Vec3b>(i)[2]=255;

        }
        else if(msg.data.at(i)==-1)
        {
            mapshow.at<Vec3b>(i)[0]=185;
            mapshow.at<Vec3b>(i)[1]=185;
            mapshow.at<Vec3b>(i)[2]=185;
        }
        else// if(msg.data.at(i)==1)
        {
            mapshow.at<Vec3b>(i)[0]=0;
            mapshow.at<Vec3b>(i)[1]=0;
            mapshow.at<Vec3b>(i)[2]=0;

        }
    }
   cout<< "msg.info.resolution"<<endl;
    for(int j=0;j<savedTrajectory.poses.size()-1;j++)
    {
        geometry_msgs::PoseStamped temp1,temp2;
        temp1=savedTrajectory.poses.at(j);
        temp2=savedTrajectory.poses.at(j+1);

//        mapshow.at<Vec3b>(Point(temp.pose.position.x/.07+512,temp.pose.position.y/.07+512))[0]=0;
//        mapshow.at<Vec3b>(Point(temp.pose.position.x/.07+512,temp.pose.position.y/.07+512))[1]=255;
//        mapshow.at<Vec3b>(Point(temp.pose.position.x/.07+512,temp.pose.position.y/.07+512))[2]=5;
       line(mapshow,Point(temp1.pose.position.x/.07+512,temp1.pose.position.y/.07+512),Point(temp2.pose.position.x/.07+512,temp2.pose.position.y/.07+512),cv::Scalar(0,255,255),2,-1);
    }


 //   arrowedLine(mapshow,a1,a2,cv::Scalar(0,0,255),2,-1,0,.5);
// doSomeThing(mapshow);
//cap>>mapshow;

    Mat img;
    img.cols=mapshow.rows;
    img.rows=mapshow.cols;
     for(int i=0;i<img.cols;i++)
     {
         for(int j=0;j<img.rows;j++)
         {
             img(i, j)=mapshow(j, i)

         }
     }







    imshow("dastan",mapshow);
    waitKey(10);
}

void map2im::trajectory_subscriber_CB(const nav_msgs::Path &msg)
{
    savedTrajectory=msg;
    geometry_msgs::PoseStamped temp;
    for(int j=0;j<savedTrajectory.poses.size();j++)
{
     temp=savedTrajectory.poses.at(0);
 //    cout<<"X="<<temp.pose.position.x/.07<<"....Y="<<temp.pose.position.y/.07<<endl;
    }


}

void map2im::slam_out_pos_subscriber_CB(const geometry_msgs::PoseStamped &msg)
{
    geometry_msgs::PoseStamped temp=msg;
    a1.x=(temp.pose.position.x)/.07+512;
    a1.y=(temp.pose.position.y)/.07+512;
    a2.x=(temp.pose.position.x+temp.pose.orientation.w)/.07*2+512;
    a2.y=(temp.pose.position.y+temp.pose.orientation.z)/.07*2+512;
}

void map2im::doSomeThing(Mat b)
{
  //  resize(b,b,Size(200,200));

    //if (img_data.size()>65535) //more than 64kB (65536)
//QImage Qframe= QImage((uchar*)m2.data, m2.cols, m2.rows, m2.step, QImage::Format_RGB555);
    imencode(".png",b,mapReadyTOSendBuff,compressParam);
    unsigned int size=mapReadyTOSendBuff.size();
    img_data.resize(size);
    for(unsigned int i=0; i<size; i++)
    img_data[i]=(unsigned char)mapReadyTOSendBuff[i];
    sendMapSoket->writeDatagram(img_data, *IP, 3434);
    sendMapSoket->flush();
//    Mat kooft ;
//    vector<uchar> ss(img_data.begin(),img_data.end());
//    imdecode(ss,CV_LOAD_IMAGE_COLOR,&kooft);


//    imshow("zahremar",b);
//    waitKey(10);
    img_data.clear();
    mapReadyTOSendBuff.clear();

}


void map2im::data_resive()
{
//  victimStatus.resize(data_map.Get_data_size());
//    victimStatus=data_map.Get_data();
//    victimStatus.resize(_socket->pendingDatagramSize());
//    _socket->readDatagram(victimStatus.data(),_socket->pendingDatagramSize());
//    _socket->flush();
    ROS_INFO("dastan");
  // emit reseived_data();
}

void hectorchatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}
