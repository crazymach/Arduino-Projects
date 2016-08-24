#include <ArduinoJson.h>

String incomingByte;

//1.Read 2. Parse 3. Do Work 4. Generate 5. Print

//must be this format:{"number": 46,"package":1351824120}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}


void loop() {
    while (Serial.available()) {
      delay(3);  //delay to allow buffer to fill 
      if (Serial.available() >0) {
        char INBYTE = Serial.read();  //gets one byte from serial buffer
        incomingByte += INBYTE; //makes the string readString
      } 
    }
  
  
  char charBuf[50];
  incomingByte.toCharArray(charBuf,50);
  
  
  StaticJsonBuffer<50> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(incomingByte);
  const char* number    = root["number"];
  long        package   = root["package"];
  if(number = 0){
    Serial.println(number);
    Serial.println(package);
  }
  delay(800);
  incomingByte = "";
}


  
