#define SampleSize 15
int DrPin = 10;
double Reading[15];
double CleanAvg;
double calibration;
double displayValue;
void setup() {
  // put your setup code here, to run once:
  pinMode(DrPin,INPUT);
  Serial.begin(9600);
  Serial.println("Press Button to begin Calibration");
//  while(digitalRead(DrPin) == LOW){
//    digitalRead(DrPin);
//  }
  Serial.println("Calibrating....");
  for(int f= 0; f<SampleSize; f++){
    calibration += analogRead(A0);
    delay(50);
  }
  calibration = calibration/SampleSize;
}

void loop() {
  // put your main code here, to run repeatedly:
//  displayValue = sensorReading()/calibration * 5
//  Serial.print(sensorReading()/calibration * 5,5);
//  Serial.println("cm");
//  delay(500);
  double voltage = analogRead(A0) * (5.0/1023.0);
  Serial.println(voltage);
  delay(500);

}
double sensorReading(){
  double sampleAvg = analogRead(A0);
  for(int i = 0; i< 15; i++){
    Reading[i] = analogRead(A0);
    delay(50);
    if(Reading[i] < sampleAvg + 1 && Reading[i] > sampleAvg-1){
      sampleAvg += Reading[i];
      sampleAvg = sampleAvg/2.00;
    }
  }

  return sampleAvg;
}


