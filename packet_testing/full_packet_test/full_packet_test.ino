#include <ArduinoJson.h>

String incomingByte;
int load_sensor;
int xcoord = 1;
int ycoord = 2;
int zcoord = 3;
int led = 13;
//1.Read 2. Parse 3. Do Work 4. Generate 5. Print


//{"seq":2,"led":0}$

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);

}


void loop() {

    while (Serial.available()) {
      char INBYTE = Serial.read();
      if (INBYTE == '$') {
         char charBuf[50];
         incomingByte.toCharArray(charBuf,50); 
 
         StaticJsonBuffer<200> jsonBuffer;
         JsonObject& root = jsonBuffer.parseObject(incomingByte);
         char Sequence    = root["seq"];
         char led_json   = root["led"];
         int incoming_sequence = Sequence;
         if(incoming_sequence > 0){
            if (led_json == 1)
              {
                blinking();
              }
          StaticJsonBuffer<200> jsonBuffer;
          JsonObject& outgoing = jsonBuffer.createObject();
          outgoing["Packet Number"] = Sequence ;
          outgoing["Sensor"] = average_calculation();
              
          JsonObject& gyro = outgoing.createNestedObject("Gyro");
          gyro["X"] = xcoord;
          gyro["Y"] = ycoord;
          gyro["Z"] = zcoord;
            
          outgoing.printTo(Serial);
          Serial.println();
            }
               incomingByte = "";
              
            }
      else {
        incomingByte += INBYTE; //add byte to json string (to parse later)
      }
      /*delay(3);  //delay to allow buffer to fill 
      if (Serial.available() >0) {
        char INBYTE = Serial.read();  //gets one byte from serial buffer
        incomingByte += INBYTE; //makes the string readString
      } */
   }
   
}  
//void json(String incomingByte){
//   char charBuf[50];
//   incomingByte.toCharArray(charBuf,50); 
// 
//   StaticJsonBuffer<200> jsonBuffer;
//   JsonObject& root = jsonBuffer.parseObject(incomingByte);
//   char Sequence    = root["seq"];
//   char led_json   = root["led"];
//   int incoming_sequence = Sequence;
//   if(incoming_sequence > 0){
//      if(led_json == 1)
//        {
//          blinking();
//        }
//      StaticJsonBuffer<200> jsonBuffer;
//      JsonObject& outgoing = jsonBuffer.createObject();
//      outgoing["Packet Number"] = Sequence ;
//      outgoing["Sensor"] = analogRead(A0) ;
//        
//      JsonObject& gyro = outgoing.createNestedObject("Gyro");
//      gyro["X"] = xcoord;
//      gyro["Y"] = ycoord;
//      gyro["Z"] = zcoord;
//        
//      outgoing.printTo(Serial);
//      Serial.println();
//      }
//  delay(800);
//}


void blinking(){
  int count = 0;
  while(count < 15){
      digitalWrite(led, HIGH);
      delay(30);
      digitalWrite(led,LOW);
      delay(30);
      count += 1;
  }
}

int average_calculation(){
  double average;
  double loadvalue;
  for(int x = 0; x <200; x++){
     loadvalue = analogRead(A0);
     average = ((loadvalue + average)/2.0);
  }
  int measurement = (int) (average * 100.0);
  return measurement;
}

  
