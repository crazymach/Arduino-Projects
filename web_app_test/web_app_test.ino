char INBYTE;
int sensorvalue;
int LED = 12;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LED,OUTPUT);
}

void loop() {

    INBYTE = Serial.read();
    sensorvalue = analogRead(A0);
//    Serial.println(sensorvalue);
    if (INBYTE == '1'){
      blinking();
      Serial.println(sensorvalue);
    }
}

  void blinking(){    //blinking of the LED
    int count = 0;              
  
    while(count <5 ){
      digitalWrite(LED,LOW);
      delay(50);
      digitalWrite(LED,HIGH);
      delay(50);
      digitalWrite(LED,LOW);
      count ++;
  }
  
}


