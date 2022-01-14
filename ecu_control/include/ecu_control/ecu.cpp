#include "ecu.h"

ECU::ECU()
{
    sock_ = InitiateCANInterface("slcan0");

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    iov.iov_base = &frame_get;
    can_msg.msg_name = & addr;
    can_msg.msg_iov = &iov;
    can_msg.msg_iovlen = 1;
    can_msg.msg_control = &ctrlmsg;

    iov.iov_len = sizeof(frame_get);
    can_msg.msg_namelen = sizeof(addr);
    can_msg.msg_controllen = sizeof(ctrlmsg);
    can_msg.msg_flags = 0;

    sleep(1);
    cout<<"******RPM Publisher Setup******"<<endl;
    ActualVel_publisher = nh.advertise<UInt16>("/TargetVel",1);

    cout<<"******Throttle Subscriber Setup"<<endl;
    TargetVel_subscriber = nh.subscribe("/ActualVel",1,&ECU::TargetVelCallback,this);


    cout<<"******Initial Target Velocity Setup******"<<endl;
    
    frame.can_id = TARGET_CAN_ID;
    frame.can_dlc = dlc;

    for(int i = 0; i < data_16;i++)
        frame.data[i] = unsigned(TargetVel_init >> 8*i);

    for(int i = data_16; i < dlc;i++)
        frame.data[i] = 0x00;

    write(sock_,&frame,sizeof(can_frame));

    sleep(3);

    cout<<"******Engine Start******"<<endl;
    frame.can_id = ENGINE_START_CAN_ID;
    frame.can_dlc = dlc;
    frame.data[0] = 0x01;
    for(int i = 1; i < dlc;i++)
        frame.data[i] = 0x00;
    
    write(sock_,&frame,sizeof(can_frame));

}

int ECU::InitiateCANInterface(const char *ifname)
{
    int sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if(sock == -1){
        printf("Fail to create CAN socket for %s - %m\n",ifname);
        return -1;
    }
    printf("Success to create CAN socket for %s \n",ifname);

    struct  ifreq ifr;
    strcpy(ifr.ifr_name, ifname);
    int ret = ioctl(sock, SIOCGIFINDEX, &ifr);

    if(ret == -1){
        perror("Fail to get CAN interface index -");
        return -1;
    }
    printf("Success to get CAN interface index: %d\n",ifr.ifr_ifindex);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    if(ret == -1)
        perror("Fail to bind CAN socket: -");
        
    return sock;
}

void ECU::TargetVelCallback(const UInt16ConstPtr & targetvel_msg)
{
    TargetVel = targetvel_msg->data;
    
    frame.can_id = TARGET_CAN_ID;
    frame.can_dlc = dlc;
    for(int i = 0; i < data_16;i++)
        frame.data[i] = (TargetVel >> 8*i);
    
    write(sock_,&frame,sizeof(can_frame));
    ReadActualVel();
}

void ECU::ReadActualVel()
{
    recvmsg(sock_,&can_msg,0);
    if(frame_get.can_id = READ_CAN_ID)
        ActualVel = ((frame_get.data[1]<<8)|(frame_get.data[0]));
    actual_vel_msg.data = ActualVel;
    ActualVel_publisher.publish(actual_vel_msg);
}

ECU::~ECU()
{

}