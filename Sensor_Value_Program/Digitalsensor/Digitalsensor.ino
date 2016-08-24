int sensorA = 2;
int sensorB = 4;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorA, INPUT);
  pinMode(sensorB, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorAstate = digitalRead(sensorA);
  int sensorBstate = digitalRead(sensorB);
  Serial.print ("SensorA");
  Serial.println(sensorAstate);

  Serial.print("SensorB");
  Serial.println( sensorBstate);
  delay(1000);
}
