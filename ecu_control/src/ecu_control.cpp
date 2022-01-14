#include <ecu_control/ecu.h>

int main(int argc,char** argv)
{
    ros::init(argc,argv,"ecu_control");

    ECU ecu_control;

    while (ros::ok())
    {
        ros::spinOnce();
    }
}