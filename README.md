# ROS_ecu_control

ECU Protocol

Term 

CAN (Controller Aera Network)

COB (Communication Object)

DLC (Data Length Code) = 8

|Object  |COB-ID == CAN ID  |DLC
|:---:|:---:|:---:|
|READ|0x100(4 byte)|8|
|Target Velocity|0x200(4 byte)|8|
|Engine Operation|0x201(4 byte)|8|

Data Info

CAN ID: 0x100

|Byte0|Byte1|Byte2|Byte3|Byte4|Byte5|Byte6|Byte7
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|Actual Velocity High Byte|Actual Velocity Low Byte|
|Target Velocity High Byte|Target Velocity Low Byte|
|Current Throttle Position High Byte|Current Throttle Position Low Byte|



CAN ID: 0x200

|Byte0  Byte1|Byte2  Byte3|Byte4  Byte5|Byte6  Byte7
|:---:|:---:|:---:|:---:|
|Target Velocity|N.A.|N.A.|N.A.
| High Byte Low Byte | N.A. | N.A. |N.A.|

CAN ID: 0x201

|Byte0  Byte1|Byte2  Byte3|Byte4  Byte5|Byte6  Byte7
|:---:|:---:|:---:|:---:|
|Start ETC|N.A.|N.A.|N.A.
| High Byte Low Byte | N.A. | N.A. |N.A.|
