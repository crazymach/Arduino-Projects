/*
 * Final Product of the Arudino Surgery https://www.youtube.com/watch?v=Jpgerv-YYAc
 * Same program as the 3-d hall effect sensor program but with JSON included as well as 
 * Ultrasonic sensors
 * JSON added for future bluetooth communication for the program
 * 
 */

#include <ArduinoJson.h>
#include<math.h>


#define dotsamt 8
#define NUM_READS 100
#define lightsize 15


const byte trig1 = 8, trig2 = 10;
const int echo1 = 7, echo2 = 9;
double Reading[15];

double light1, light2;
int dots = 0;
double ping1,ping2,pingAvg;


int Zaxis = 0, botL = 1, botR = 2,midR = 3, midL = 4,
topL = 6, topR = 7, top = 5 ;
double NoZ, NobotL,NobotR, NotopR, NotopL, Notop, NomidR, NomidL;
double magnetZ,magnetbotL, magnetbotR, magnettopL,magnettopR,magnettop, magnetmidR, magnetmidL;
int readingZ,readingbotL,readingbotR,readingtopR,readingtopL,readingmidL, readingmidR, readingtop;
int inByte = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  NoZ = readSensor(Zaxis);
  NobotL = readSensor(botL);
  NobotR = readSensor(botR);
  NotopR = readSensor(topR);
  NotopL = readSensor(topL);
  Notop  = readSensor(top);
  NomidL = readSensor(midL);
  NomidR = readSensor(midR);

    while(!Serial){
    ;
  }
  establishContact();
}

void loop() {
  if(Serial.available() > 0){
    inByte = Serial.read();
    magnetZ    = readSensor(Zaxis);
    magnetbotL = readSensor(botL);
    magnetbotR = readSensor(botR);
    magnettopL = readSensor(topR);
    magnettopR = readSensor(topL);
    magnettop  = readSensor(top);
    magnetmidR = readSensor(midR);
    magnetmidL = readSensor(midL);

    readingZ  =   abs(NoZ - magnetZ);
    readingbotL = abs(NobotL - magnetbotL);
    readingbotR = abs(NobotR - magnetbotR);
    readingtopR = abs(NotopR - magnettopL)*3;
    readingtopL = abs(NotopL - magnettopR)*3;
    readingtop  = abs(Notop - magnettop);
    readingmidR = abs(NomidR - magnetmidR);
    readingmidL = abs(NomidL - magnetmidL);
    int ping1 = ping(trig1,echo1)/ 58 - 10;
//    delay(100);
//    ping2 = ping(trig2,echo2)/ 58;
//    int pingAvg = (ping1 + ping2)/2;

//
//    Serial.print(readingZ); Serial.print("\t");
//    Serial.print(readingbotL); Serial.print("\t");
//    Serial.print(readingbotR); Serial.print("\t");
//    Serial.print(readingtopR); Serial.print("\t");
//    Serial.print(readingtopL); Serial.print("\t");
//    Serial.print(readingmidR); Serial.print("\t");
//    Serial.print(readingmidL); Serial.print("\t");
//    Serial.print(readingtop);  Serial.print("\t");
//    Serial.println(ping1);Serial.print("\t");
    Serial.write(readingZ);
    Serial.write(readingbotL);
    Serial.write(readingbotR);
    Serial.write(readingtopR);
    Serial.write(readingtopL);
    Serial.write(readingmidR);
    Serial.write(readingmidL);
    Serial.write(readingtop);
//    Serial.write(ping1);
  }

}




void jsonGenerate(double ping1, double ping2, double pingAvg){//JSON used to send packets of the sensor data
  String Str1 = String(ping1) + " m";
  String Str2 = String(ping2) + " m";
  String StrAvg = String(pingAvg) + " m";
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["Sensor1"] = Str1;
  root["Sensor2"] = Str2;
  root["Sensor Average"] = StrAvg;
  root.prettyPrintTo(Serial);
}

 double ping(int trig, int echo){
  digitalWrite(trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig,LOW);
  return double(pulseIn(echo,HIGH));
}


void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}

double readSensor(int sensorpin){
   // read multiple values and sort them to take the mode
   int sortedValues[NUM_READS];
   for(int i=0;i<NUM_READS;i++){
     int value = analogRead(sensorpin);
     int j;
     if(value<sortedValues[0] || i==0){
        j=0; //insert at first position
     }
     else{
       for(j=1;j<i;j++){
          if(sortedValues[j-1]<=value && sortedValues[j]>=value){
            // j is insert position
            break;
          }
       }
     }
     for(int k=i;k>j;k--){
       // move all values higher than current reading up one position
       sortedValues[k]=sortedValues[k-1];
     }
     sortedValues[j]=value; //insert current reading
   }
   //return scaled mode of 10 values
   float returnval = 0;
   for(int i=NUM_READS/2-5;i<(NUM_READS/2+5);i++){
     returnval +=sortedValues[i];
   }
//   return returnval = returnval/10;
   return returnval * (255/10230.0);
}
