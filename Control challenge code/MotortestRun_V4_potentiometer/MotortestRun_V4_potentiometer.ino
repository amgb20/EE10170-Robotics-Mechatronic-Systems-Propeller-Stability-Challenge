// controler le motor avec le potentiometre 

int pwmA = 5;
int in1A = 2;
int in2A = 4;
int stby = 9;

int MotorSpeed1 = 0;

int ch;

void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200); 
  pinMode(pwmA, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
    
  Serial.println("1: forward, 2: backward and s to stop ");
}

// the loop routine runs over and over again forever:
void loop() 
{
  if (Serial.available())
  {
    char ch = Serial.read();
    
    while (ch == '1')
    {
      int sensorValue = analogRead(A0);

      digitalWrite(in1A, HIGH);
      digitalWrite(in2A, LOW);
      digitalWrite(stby, HIGH);
      
      MotorSpeed1 = sensorValue ;
      
      analogWrite(pwmA, MotorSpeed1);
    
      delay(1);        // delay in between reads for stability
    }

    while (ch == '2')
    {
      int sensorValue = analogRead(A0);

      digitalWrite(in1A, LOW);
      digitalWrite(in2A, HIGH);
      digitalWrite(stby, HIGH);
      
      MotorSpeed1 = sensorValue ;
      
      analogWrite(pwmA, MotorSpeed1);
    
      delay(1);        // delay in between reads for stability
    }

    
     }
     while (ch == 's')
     {
       digitalWrite(in1A, LOW);
       digitalWrite(in2A, LOW);
       digitalWrite(stby, LOW);

       analogWrite(pwmA, 0);
  
     }
  }
      
