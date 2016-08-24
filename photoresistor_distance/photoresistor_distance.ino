int ledPin = 6;
int ldrPin = 0;
int lightVal = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading;
  float voltage;
  reading = analogRead(ldrPin);
  voltage = reading * (5.0/1023.0);

  lightVal = analogRead(ldrPin);
  digitalWrite(ledPin,HIGH);
//  delay(lightVal);
//  digitalWrite(ledPin,LOW);
//  delay(lightVal);
  Serial.println(voltage);
  delay(500);
//  if (voltage < 2.0){
//    Serial.println((analogRead(ldrPin*(5.0/1023.0))));
//  }
//  delay(10);
//  if (voltage < 2.25){
//    Serial.println((analogRead(ldrPin*(5.0/1023.0))));
//  }
//  delay(10);
//  if (voltage < 2.5){
//    Serial.println((analogRead(ldrPin*(5.0/1023.0))));
//  }
//  delay(10);
//  if (voltage < 3.0){
//    Serial.println((analogRead(ldrPin*(5.0/1023.0))));
//  }
//  delay(10);
//  
}
