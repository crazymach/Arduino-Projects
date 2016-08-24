double CurrentSensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  CurrentSensor = analogRead(A0) * (5.0/1023.0);
  Serial.println(CurrentSensor,4);
  delay(500);
}
