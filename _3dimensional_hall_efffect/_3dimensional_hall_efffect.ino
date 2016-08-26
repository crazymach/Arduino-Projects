/*
 * This sketch measures the magnetic field strength in proximity to 
 * a Hall effect sensor. The program interprepts the values into coordinates
 * in a 3-d space, and processing can later take the values and 
 * place it in the 3-d coordinate system
 */
#include<math.h>
#define NUM_READS 100


int Zaxis = 0, botL = 1, botR = 2,topR = 3, topL = 4, top = 5 ; //Analog Pins for the Hall effect sensors
double NoZ, NobotL,NobotR, NotopR, NotopL, Notop; //No magnet in the presence
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
  while(!Serial){     //Establishes contact with Processing or whatever Serial Contact
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

    readingZ  =   abs(NoZ - magnetZ);//Subtracts No magnet from magnet field strength to give coordiantes
    readingbotL = abs(NobotL - magnetbotL);
    readingbotR = abs(NobotR - magnetbotR);
    readingtopR = abs(NotopR - magnettopL);
    readingtopL = abs(NotopL - magnettopR);
    readingtop  = abs(Notop - magnettop);


//    Serial.print(readingZ); Serial.print("\t"); //Uncomment to see raw values
//    Serial.print(readingbotl); Serial.print("\t");
//    Serial.print(readingbotr); Serial.print("\t");
//    Serial.print(readingtopr); Serial.print("\t");
//    Serial.print(readingtopl); Serial.print("\t");
//    Serial.println(readingtop);
    Serial.write(readingZ); //Writes to the Serial Monitor
    Serial.write(readingbotL);
    Serial.write(readingbotR);
    Serial.write(readingtopR);
    Serial.write(readingtopL);
    Serial.write(readingtop);
  }
}

double readSensor(int sensorpin){ //Median Filtering to get consistent values
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


void establishContact() { //Method for fetch and response for Serial Monitor
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}


