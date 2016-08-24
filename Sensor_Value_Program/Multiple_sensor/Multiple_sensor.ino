void setup() {
  
  Serial.begin(9600);

}

void loop() {
  
  int sensorValueA = analogRead(A0); // gives analog values for the sensors
  int sensorValueB = analogRead(A1);

  
  Serial.print("Sensor Value A: "); // gives the individual values for the sensor
  Serial.println(sensorValueA);
  Serial.print("Sensor Value B: ");
  Serial.println(sensorValueB);

// uncomment to show when the sensor is being pressed without values
//
//  if (sensorValueA <300)
//    {
//      Serial.println ("SensorA is pressed");
//      
//    }
//   if (sensorValueB < 300)
//    {
//      Serial.println ("SensorB is Pressed");
//      
//    }

  delay (800); // change for the speed of serial monitor
}
