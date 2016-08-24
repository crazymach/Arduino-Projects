#define sampleSize 50
#define dotsamt 5
int dots = 0;
int photo1 = 0, photo2 = 1;
double light1, light2;
int reading1,reading2;
float voltage1, voltage2;
void setup() {
  
  Serial.begin(9600); // the bigger number the better


}

void loop() {

  reading1 = analogRead(photo1);reading2 = analogRead(photo2);
  voltage1 = reading1 * (5.0/1023.0);
  voltage2 = reading2 * (5.0/1023.0);
  Serial.println(voltage1);
//  voltages();
  delay(50);
  

}

void voltages(){
  if(voltage1 <.4){
    Serial.println(log((analogRead(photo1) * 5.0/1023.0)-(.6118)/(-.0302)));
  }
  delay(10);
  if(voltage1 <.5){
    Serial.println(log((analogRead(photo1) * 5.0/1023.0)-(.6118)/(-.0302)));
  }
  delay(10);
  if(voltage1 < .6){
    Serial.println(log((analogRead(photo1) * 5.0/1023.0)-(.6118)/(-.0302)));
  }
  delay(10);
  if(voltage1 <.7){
    Serial.println(log((analogRead(photo1) * 5.0/1023.0)-(.6118)/(-.0302)));
  }
  delay(10);
}




