double CurrentSensor;
void setup() {
  // put your setup code here, to run once:
  Serial.println("CLEARDATA");
  Serial.println("CLEARSHEET");
  Serial.println("LABEL,TIME,Voltage");
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  CurrentSensor = analogRead(A0) * (5.0 / 1023.0);
  Serial.print("DATA,TIME,"); 
  Serial.println(CurrentSensor);
  delay(500);
}
