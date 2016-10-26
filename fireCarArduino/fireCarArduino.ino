#include <Servo.h> 
#include <SoftwareSerial.h>

SoftwareSerial espSerial(14, 15); // RX, TX

Servo tMotor;
Servo dServo;
int tPin = 11;
int dPin = 10;
int tDefaultPosition = 35;
int dDefaultPosition = 90;

void setup() 
{
  tMotor.attach(tPin);
  dServo.attach(dPin);
  
  tMotor.write(tDefaultPosition);
  dServo.write(dDefaultPosition);

  Serial.begin(19200);
  espSerial.begin(19200);
} 
 
void loop() 
{ 
  static int v = 0;

  if ( espSerial.available()) {
    char ch = espSerial.read();
    Serial.print(ch);

    switch(ch) {
      case '0'...'9':
        v = v * 10 + ch - '0';
        break;
      case 't':
        tMotor.write(v);
        v = 0;
        break;
      case 'd':
        dServo.write(v);
        v = 0;
        break;
    }
  }
} 

