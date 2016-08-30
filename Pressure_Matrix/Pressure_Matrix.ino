#define NUM_READS 50


int velo0 = 0, velo1 = 1, velo2 = 2, velo3 = 3;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int read0 = readSensor(velo0);
  int read1 = readSensor(velo1);
  int read2 = readSensor(velo2);
  int read3 = readSensor(velo3);
  Serial.print(read0,DEC); Serial.print("\t");
  Serial.print(read1,DEC); Serial.print("\t");
  Serial.print(read2,DEC); Serial.print("\t");
  Serial.println(read3,DEC);

}

int readSensor(int sensorpin){
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
   return returnval/10;  //returns voltage values)
}

