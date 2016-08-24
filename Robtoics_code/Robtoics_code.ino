#include <Servo.h>
Servo myServo;
Servo myServo2;


void setup()
{
	Serial.begin(9600); //channel that the computer uses to talk to the arduino
    myServo.attach(6);
    myServo2.attach(7);
}

void loop()
{
	pinMode(3,OUTPUT); //setup pin
	digitalWrite(3,HIGH); //fill capacitor with voltage
	delayMicroseconds(10);
	pinMode(3,INPUT); //setup pin
	digitalWrite(3,LOW); //start draining the capacitor
	int timer = micros(); //get initial time
	while(digitalRead(3) == HIGH); //moves to next line when this is false
	timer = micros() - timer;  //get time taken to discharge the capacitor
	Serial.println(timer); //print timer value to the serial port
	if(timer > 350)
	{
		myServo.write(180);
		myServo2.write(0);
	}else
	{
		myServo.write(180);
		myServo2.write(180);
		delay(1500);
		myServo.write(180);
		myServo2.write(0);
	}



}

