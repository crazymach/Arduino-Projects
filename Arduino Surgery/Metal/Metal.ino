int ledPin = 3;
int sw = 7;
int bright = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(sw, INPUT);

}

void loop() {
  if(digitalRead(sw) == HIGH){
    if(bright == 250){
      while(bright > 5){
        analogWrite(ledPin,bright);
        bright--;
        Serial.println(analogRead(A0));
        delay(10);
      }
    }
    analogWrite(ledPin,bright);
    bright++;
    delay(10);
  }
  else{
    digitalWrite(ledPin,LOW);  Serial.println(analogRead(A0));

  }
}
