#ifndef ECU_H
#define ECU_H
#include <ros/ros.h>
#include <std_msgs/UInt16.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>

using std_msgs::UInt16;
using std_msgs::UInt16ConstPtr;

using std::cout;
using std::endl;

class ECU{
    public:
    // Constructor
    ECU();

    int InitiateCANInterface(const char *ifname);

    void TargetVelCallback(const UInt16ConstPtr & targetvel_msg);

    void ReadActualVel();

    ~ECU();

    private:
    struct sockaddr_can addr;
    struct can_frame frame;
    struct canfd_frame frame_fd;

    struct iovec iov;
    struct msghdr can_msg;
    char ctrlmsg[CMSG_SPACE(sizeof(struct timeval) + 3*sizeof(struct timespec) + sizeof(__u32))];
    struct canfd_frame frame_get;

    struct timeval tv;

    int sock_;

    ros::NodeHandle nh;
    ros::Publisher ActualVel_publisher;
    ros::Subscriber TargetVel_subscriber;

    double last_time = ros::Time::now().toSec();

    uint16_t TargetVel;
    const uint16_t TargetVel_init = 2000;
    uint16_t ActualVel;

    const int dlc = 8;
    const int data_16 = 2;

    const int READ_CAN_ID = 0x100;
    const int TARGET_CAN_ID = 0x200;
    const int ENGINE_START_CAN_ID = 0x201;
    UInt16 actual_vel_msg;
};



#endif