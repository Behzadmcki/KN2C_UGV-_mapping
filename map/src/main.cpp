#include "map.h"

int main(int argc, char **argv  ){

    ros::init(argc,argv,"map");
    ros::NodeHandle nh;
    map2im map;
    ros::Subscriber sub = nh.subscribe("map",1,&map2im::Map_subscriber_CB,&map);
    ros::Subscriber sub = nh.subscribe("map",1,hectorchatterCallback);
    ros::Subscriber sub1= nh.subscribe("trajectory",1,&map2im::trajectory_subscriber_CB,&map);
    ros::Subscriber sub2= nh.subscribe("slam_out_pose",1,&map2im::slam_out_pos_subscriber_CB,&map);
    ros::spin();

    return 0;
}
