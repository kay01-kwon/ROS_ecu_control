# ROS_ecu_control

ECU Protocol

Term 

CAN (Controller Aera Network)

COB (Communication Object)

DLC (Data Length Code) = 8

|Object  |COB-ID == CAN ID  |DLC
|:---:|:---:|:---:|
|READ|0x100(4 byte)|8|
|Target Vel|0x200(4 byte)|8|
|Engine Op|0x201(4 byte)|8|
