/*
 * Utilizes two photo resistor to measure distance
 */
int photo1 = 0, photo2 = 1;
double Reading[15];
double read1, read2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    read1 = sensorReading(photo1);
    read2 = sensorReading(photo2);
    delay(500);
}

double sensorReading(int photo){
  double sampleAvg = analogRead(photo);
  for(int i = 0; i< 15; i++){
    Reading[i] = analogRead(photo);
    delay(50);
    if(Reading[i] < sampleAvg + 1 && Reading[i] > sampleAvg-1){
      sampleAvg += Reading[i];
      sampleAvg = sampleAvg/2.00;
    }
  }

  return sampleAvg;
}

