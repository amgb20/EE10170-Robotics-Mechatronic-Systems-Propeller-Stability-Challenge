#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

// Motor A

int pwmA = 5;
int in1A = 2;
int in2A = 4;
int stby = 9;

int MotorSpeed1 = 0;

int16_t AccRaw_X, AccRaw_Y, AccRaw_Z, GyrRaw_X, GyrRaw_Y, GyrRaw_Z;

float AccAngle[2];
float GyroAngle[2];
float TotAngle[2];

float elapsedTime, time, timePrev;
int i;
float rad_to_deg = 180/3.141592654;

float PID, error, previous_error;
float pid_p = 0;
float pid_i = 0;
float pid_d = 0;

double kp = 4;
double ki = 0.048;
double kd = 2 ;

double Throttle = 1300;
float Demand_angle = 45;

void setup()
{
  Serial.begin(115200); 
  pinMode(pwmA, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
 
  Wire.begin(); //begin the wire communication
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  time= millis();
  

}

void loop()
{

    timePrev = time;
    time = millis();
    elapsedTime = (time - timePrev) / 1000;
  
    Wire.beginTransmission(0x68);
    Wire.write(0x3B);
    Wire.write(0);
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 6, true);
    
    AccRaw_X = Wire.read()<<8|Wire.read();
    AccRaw_Y = Wire.read()<<8|Wire.read();
    AccRaw_Z = Wire.read()<<8|Wire.read();
  
    AccAngle[0] = atan((AccRaw_Y/16384.0)/sqrt(pow((AccRaw_X/16384.0),2)+ pow((AccRaw_Z/16384.0),2)))* rad_to_deg;
    AccAngle[1] = atan(-1*(AccRaw_X/16384.0)/sqrt(pow((AccRaw_Y/16384.0),2) + pow((AccRaw_Z/16384.0),2)))* rad_to_deg;
  
    Wire.beginTransmission(0x68);
    Wire.write(0x43);
    Wire.write(0);
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 4, true);
  
    GyrRaw_X = Wire.read()<<8|Wire.read();
    GyrRaw_Y = Wire.read()<<8|Wire.read();
  
    GyroAngle[0] = GyrRaw_X/131.0;
    GyroAngle[1] = GyrRaw_Y/131.0;
  
    TotAngle[0] = 0.98 * (TotAngle[0] + GyroAngle[0] * elapsedTime) + 0.02 * AccAngle[0];
    TotAngle[1] = 0.98 * (TotAngle[1] + GyroAngle[1] * elapsedTime) + 0.02 * AccAngle[1];
  
    error = TotAngle[1] - Demand_angle;
    
    pid_p = kp * error;

    if(-5 <error <5)
    {
      pid_i = pid_i + (ki * error);
    }
    
    pid_d = kd * ((error - previous_error)/elapsedTime);
  
    PID = pid_p + pid_i + pid_d;
  
    digitalWrite(in1A, HIGH);
    digitalWrite(in2A, LOW);
    digitalWrite(stby, HIGH); 
  
    MotorSpeed1 = PID + Throttle ;

    analogWrite(pwmA, MotorSpeed1);
        
    delay(10000);
  
}
 
  
