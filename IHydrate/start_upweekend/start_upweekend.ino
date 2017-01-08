char INBYTE;
int depthsensor = A0;
int loadsensor = A1;
int LED = 12;
float depthreading;
float loadreading;
int count = 0;

void setup(){
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop(){
  
  depthreading = depth(depthsensor);
//  loadreading = load(loadsensor);
//  Serial.print("Depth reading");
//  Serial.print("Weight reading");
//  Serial.println(loadreading);
    Serial.println(depthreading);
  delay(500);
  INBYTE = Serial.read();
  if(INBYTE == '0') {
    Serial.println(depthreading);
  }
  else if(INBYTE == '1') {
    Serial.println(depthreading);
    blinking(count);
  }


     
}
float depth(int depthsensor){
  float reading;
  reading = analogRead(depthsensor);
  reading = (1023 / reading) - 1;
  reading = 560 / reading;
  
  return reading;
}

float load(int loadsensor){
  float reading;
  reading = analogRead(loadsensor);
  return reading;
}
void blinking(int count){
  while(count <5 ){
    digitalWrite(LED,LOW);
    delay(50);
    digitalWrite(LED,HIGH);
    delay(50);
    digitalWrite(LED,LOW);
    count ++;
  }
  count = 0;
}

