#include <ArduinoJson.h>



int Packetnumber;
int SensorValue = analogRead(A0);
int xcoord = analogRead(A1);
int ycoord = analogRead(A2);
int zcoord = analogRead(A3);
String incomingByte;


String readline;


void setup() {
  Serial.begin(9600);  

}

void loop() {
  String stringOne = "A long integer: ";
  stringOne += 123456789;
  char charBuf[50];
  stringOne.toCharArray(charBuf, 50);

  Serial.println(stringOne);
 

}
