#include <ArduinoJson.h>

//1.Read 2. Parse 3. Do Work 4. Generate 5. Print
int PacketNumber = 1;
int SensorValue = analogRead(A0);
int xcoord = 1;
int ycoord = 2;
int zcoord = 3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}


void loop() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& outgoing = jsonBuffer.createObject();
  outgoing["Packet Number"] = 1 ;
  outgoing["Sensor"] = analogRead(A0) ;
  
  JsonObject& gyro = outgoing.createNestedObject("Gyro");
  gyro["X"] = xcoord;
  gyro["Y"] = ycoord;
  gyro["Z"] = zcoord;

  outgoing.printTo(Serial);
  Serial.println();
  // This prints:
  // {"sensor":"gps","time":1351824120,"data":[48.756080,2.302038]}
  
  delay(500);
}


  
