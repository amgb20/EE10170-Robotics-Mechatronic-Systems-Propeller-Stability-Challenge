#include<Wire.h>

const int MPU_addr=0x68; // IC2 adress of the MPU-6050

int16_t AcX,AcY,AcZ,GyX,GyY,GyZ; // variables for the accelerometer and gyroscope data

int minVal=265;
int maxVal=402;

double Angle_X;
double Angle_Y;
double Angle_Z;
 


void setup(){
  Wire.begin(); // Initiate the Wire library
  Wire.beginTransmission(MPU_addr); // Begin a transmission to the I2C slave
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // activate the MPU
  Wire.endTransmission(true);
  Serial.begin(115200);
}
void loop(){
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); //starting with register Ox3B
  Wire.endTransmission(false); //the parameter indicates that the arduino will send a restart 
  Wire.requestFrom(MPU_addr,14,true); //request a total of 14 registers
  
  AcX=Wire.read()<<8|Wire.read(); //reading registers: 0x3B and 0x3C
  AcY=Wire.read()<<8|Wire.read();//reading registers: 0x3D and 0x3E
  AcZ=Wire.read()<<8|Wire.read();//reading registers: 0x3F and 0x30
  
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  Angle_X= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI); // The atan2() function computes the principal value of the arc tangent 
  Angle_Y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI); // of __y / __x, using the signs of both arguments to determine the quadrant 
  Angle_Z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI); //of the return value. The returned value is in the range [-pi, +pi] radians

     Serial.print("AngleX= ");
     Serial.println(Angle_X);

     Serial.print("AngleY= ");
     Serial.println(Angle_Y);

     Serial.print("AngleZ= ");
     Serial.println(Angle_Z);
     Serial.println("-----------------------------------------");
     delay(300);
}
