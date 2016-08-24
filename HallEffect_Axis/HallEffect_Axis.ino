
#define factorX .3951
#define factorY .8318
#define exponentX .9666
#define exponentY .7904

#define NUM_READS 200
double CurrentSensorX, CurrentSensorY;

double calibrationX, calibrationY;
double beforeX, beforeY; 
void setup() {
  Serial.begin(9600);
  calibrationX = readSensor(calibrationX);
  calibrationY = readSensor(calibrationY);
}
void loop() {
  // put your main code here, to run repeatedly:
  beforeX = readSensor(A0);
  beforeY = readSensor(A1);
  CurrentSensorX = abs(axisParseX(calibrationX) - axisParseX(beforeX));
  CurrentSensorY = abs(axisParseY(calibrationY) - axisParseY(beforeY));
  Serial.print(beforeX); Serial.print("\t");  
  Serial.print(beforeY);Serial.print("\t");
  Serial.print(CurrentSensorX);Serial.print("\t");
  Serial.println(CurrentSensorY);
  delay(10);
}

float readSensor(int sensorpin){
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
   returnval = returnval/10;
   return returnval * (5.0/1023.0);
}

double axisParseX(double axis){
    double calculation = exp((axis * exponentX) *factorX);
    return calculation ;
}
double axisParseY(double axis){
    double calculation = exp((axis * exponentY)*factorY);
    return calculation ;
}

