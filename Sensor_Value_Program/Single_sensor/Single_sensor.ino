void setup() {
  
  Serial.begin(9600);

}

void loop() {
  
  int sensorValue = analogRead(A0); // gives analog values for the sensors
  

  
  Serial.print("Sensor Value: "); // gives the individual values for the sensor
  Serial.println(sensorValue);

// uncomment to show when the sensor is being pressed without values
//
//  if (sensorValueA <300)
//    {
//      Serial.println ("SensorA is pressed");
//      
//  

  delay (800); // change for the speed of serial monitor
}
