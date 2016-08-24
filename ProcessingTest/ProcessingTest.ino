char val;

void setup() {
 Serial.begin(9600);
}
 
void loop() {
 if(Serial.available()){
    val = Serial.read();
 }
 int analogValue = analogRead(A0)/4; // read the sensor value
 if(val == '1')
  {
    Serial.write("hello World");          // send the value serially
  }
  else{
    Serial.write(analogValue);
  }
  delay(500);
}
