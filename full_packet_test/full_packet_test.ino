#include <ArduinoJson.h>
#include<Wire.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

String incomingByte;
float loadvalue;
float average;
int load_sensor;
int xcoord = 1;
int ycoord = 2;
int zcoord = 3;
int led = 13;
//1.Read 2. Parse 3. Do Work 4. Generate 5. Print


//{"seq":2,"led":0}$

void setup() {
  // put your setup code here, to run once:
    Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(led, OUTPUT);

}


void loop() {


    while (Serial.available()) {
      char INBYTE = Serial.read();
      MPU();
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
          gyro["GyX"] = GyX;
          gyro["GyY"] = GyY;
          gyro["GyZ"] = GyZ;

          JsonObject& Accel = outgoing.createNestedObject("Accel");
          Accel["AcX"] = AcX;
          Accel["AcY"] = AcY;
          Accel["AcZ"] = AcZ;

          outgoing["Temp"] = Tmp;
          
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

float average_calculation(){
  for(int x = 0; x <200; x++){
    loadvalue = analogRead(A0);
    average = (loadvalue + average)/2;
  }
  float calculation = average;
  return calculation;
}

void MPU(){
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
        AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
        AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
        AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
        Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
        GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
        Tmp = Tmp/340.00+36.53;

}
  
