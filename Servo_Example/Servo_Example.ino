#include <Servo.h>

Servo myServo;
Servo myServo2;

void setup()
{
  myServo.attach(3); 
}

void loop()
{
  myServo.write(180);
  
  


}
