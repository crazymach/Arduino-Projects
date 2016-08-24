#include<math.h>
#define NUM_READS 100


int Zaxis = 0, botL = 1, botR = 2,topR = 3, topL = 4, top = 5 ;
double NoZ, NobotL,NobotR, NotopR, NotopL, Notop;
double magnetZ,magnetbotL, magnetbotR, magnettopL,magnettopR,magnettop;
int readingZ,readingbotL,readingbotR,readingtopR,readingtopL, readingtop;
int inByte = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  NoZ = readSensor(Zaxis);
  NobotL = readSensor(botL);
  NobotR = readSensor(botR);
  NotopR = readSensor(topR);
  NotopL = readSensor(topL);
  Notop  = readSensor(top);
  while(!Serial){
    ;
  }
  establishContact();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    inByte = Serial.read();
    magnetZ    = readSensor(Zaxis);
    magnetbotL = readSensor(botL);
    magnetbotR = readSensor(botR);
    magnettopL = readSensor(topR);
    magnettopR = readSensor(topL);
    magnettop  = readSensor(top);

    readingZ  =   abs(NoZ - magnetZ);
    readingbotL = abs(NobotL - magnetbotL);
    readingbotR = abs(NobotR - magnetbotR);
    readingtopR = abs(NotopR - magnettopL);
    readingtopL = abs(NotopL - magnettopR);
    readingtop  = abs(Notop - magnettop);


//    Serial.print(readingZ); Serial.print("\t");
//    Serial.print(readingbotl); Serial.print("\t");
//    Serial.print(readingbotr); Serial.print("\t");
//    Serial.print(readingtopr); Serial.print("\t");
//    Serial.print(readingtopl); Serial.print("\t");
//    Serial.println(readingtop);
    Serial.write(readingZ);
    Serial.write(readingbotL);
    Serial.write(readingbotR);
    Serial.write(readingtopR);
    Serial.write(readingtopL);
    Serial.write(readingtop);
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


void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}


