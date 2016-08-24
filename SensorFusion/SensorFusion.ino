#include <ArduinoJson.h>
#include<math.h>


#define dotsamt 8
#define sampleSize 100
#define lightsize 15

int trig1 = 8, trig2 = 10;
int echo1 = 7, echo2 = 9;
int sw = 6, photo1 = 0, photo2 = 1;
double Reading[15];
double light1, light2;
int dots = 0;
double ping1,ping2,pingAvg;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(sw,INPUT);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  ping1 = ping(trig1,echo1)/1000-1;
  delay(100);
  ping2 = ping(trig2,echo2)/1000 -1;
  pingAvg = (ping1 + ping2)/2;

  jsonGenerate(ping1,ping2,pingAvg);
  delay(509);
}

void jsonGenerate(double ping1, double ping2, double pingAvg){
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



float readSensor(int sensorpin){
   // read multiple values and sort them to take the mode
   int sortedValues[sampleSize];
   for(int i=0;i<sampleSize;i++){
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
   for(int i=sampleSize/2-5;i<(sampleSize/2+5);i++){
     returnval +=sortedValues[i];
   }
   returnval = returnval/10;
   return returnval*5/1023;
}
