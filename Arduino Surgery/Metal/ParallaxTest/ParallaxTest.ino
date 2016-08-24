#define sampleSize 50
#define dotsamt 5
int dots = 0;
int photo1 = 0, photo2 = 1;
double light1, light2;
int trig1 = 8, trig2 = 10;
int echo1 = 7, echo2 = 9;
double ping1,ping2,pingAvg;
double Reading[15];
double calibration1, calibration2;
void setup() {
  
  Serial.begin(9600); // the bigger number the better
   Serial.println("CLEARDATA");
  Serial.println("CLEARSHEET"); //clears up any data left from previous projects
  Serial.println("LABEL,TIME,PingAvg,Light1,Light2");
  pinMode(trig1,OUTPUT);
  pinMode(trig2,OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2,INPUT);

  for(int i =0; i < sampleSize; i++){
    calibration1 += ping(trig1,echo1);
    delay(10);
  }
  calibration1 = calibration1/sampleSize;
  dots = 0;
  for(int i =0; i < sampleSize; i++){
    calibration2 += ping(trig2,echo2);
    delay(10);
  }
  calibration2 = calibration2/sampleSize;

}

void loop() {
  ping1 = ping(trig1,echo1)/calibration1 * 10;
  delay(100);
  ping2 = ping(trig2,echo2)/calibration2 * 10;
  pingAvg = (ping1 + ping2)/2;
  light1 = sensorReading(photo1);
  light2 = sensorReading(photo2);
  Serial.print("DATA,TIME,"); 
  Serial.print(pingAvg); Serial.print(",");
  Serial.print(light1);Serial.print(","); 
  Serial.println(light2);

}


double sensorReading(int photo){
  double sampleAvg = analogRead(photo);
  for(int i = 0; i< 15; i++){
    Reading[i] = analogRead(photo);
    delay(5);
    if(Reading[i] < sampleAvg + 1 && Reading[i] > sampleAvg-1){
      sampleAvg += Reading[i];
      sampleAvg = sampleAvg/2.00;
    }
  }
  return sampleAvg;
}

double ping(int trig, int echo){
  digitalWrite(trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig,LOW);
  return pulseIn(echo,HIGH);
}

