#define sampleSize 15

double Reading[15];

void setup() {
 Serial.begin(9600);
}

void loop() {
  delay(100);
}


double cleanValue(){
  double sampleAvg = analogRead(A0);
  for(int i = 0; i < sampleSize; i ++){
    Reading[i] = analogRead(A0);
    if(Reading[i] < sampleAvg + 1.5 && Reading[i] > sampleAvg - 1.5){
      sampleAvg += Reading[i];
      sampleAvg = sampleAvg/2;
    }
  }return sampleAvg;
}

