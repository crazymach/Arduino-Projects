#include <ArduinoJson.h>

//1.Read 2. Parse 3. Do Work 4. Generate 5. Print
int PacketNumber = 1;
int SensorValue = analogRead(A0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}


void loop() {
  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  root["sensor"] = analogRead(A0);
  root["time"] = 1 ;
  
  JsonArray& data = root.createNestedArray("data");
  data.add(48.756080, 6);  // 6 is the number of decimals to print
  data.add(2.302038, 6);   // if not specified, 2 digits are printed
  
  root.prettyPrintTo(Serial);
  // This prints:
  // {"sensor":"gps","time":1351824120,"data":[48.756080,2.302038]}
  
  delay(500);
}


  
