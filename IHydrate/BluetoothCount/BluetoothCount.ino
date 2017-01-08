int counter = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(50);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  counter++;
  Serial.print("Arduino Counter");
  Serial.println(counter);
  delay(500);
}
