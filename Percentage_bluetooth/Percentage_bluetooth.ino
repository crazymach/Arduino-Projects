char INBYTE;
int LED = 12;
float emptyaverage = 0;
float fullaverage = 0;
float after = 0;
float loadvalue;
float average;
float value;
float total_water;
int   sensor;

void setup() {
    Serial.begin(9600);
    pinMode(LED,OUTPUT);
//    calibration();


}

void loop() {

    INBYTE = Serial.read();
//      int read_value = analogRead(A0) * 43.75 ;
//      Serial.println(read_value);
//    float average_value = average_calculation();
    sensor = analogRead(A0);
    Serial.println(sensor,5);
    if (INBYTE == '1'){
      blinking();
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
//float calibration(){
//  calibration_empty();
//  calibration_full();
//  while(fullaverage < emptyaverage){
//      
//    Serial.println("Recalibration is necessary");
//    calibration_empty();
//    calibration_full();
//  }
//    total_water = (fullaverage - emptyaverage);
//    Serial.print("The amount of water in the cup is");
//    Serial.println(total_water);
//    
//    return total_water;
//}
//
//float calibration_empty(){
//    float before = analogRead(A0);
//
//      delay(50);
//      Serial.println("Press 1 for to begin calibration");
//      if (INBYTE == '1'){
//      average_empty_calibration();
//      }
//      Serial.println("DONE!");
//      Serial.println(emptyaverage,5);
//
//}
//float calibration_full(){
//   Serial.println("Place the full water bottle onto the Quench");
//   float before = analogRead(A0);
//   while(after < (before + 50)){
//     after = analogRead(A0);
//   }
//   average_full_calibration();
//   Serial.println("DONE!");
//   Serial.println(fullaverage,5);
//
//}
//
//float average_empty_calibration(){
//  for(int x = 0; x <1000; x ++){
//      loadvalue = analogRead(A0);
//      emptyaverage = (emptyaverage + loadvalue)/ 2;
//      delay(10);
//  }
//  return emptyaverage;
//
//}
//float average_full_calibration(){
//  for(int x = 0; x <1000; x ++){
//      loadvalue = analogRead(A0);
//      fullaverage = (fullaverage + loadvalue)/ 2;
//      delay(10);
//  }
//  return fullaverage;
//
//}
float average_calculation(){
  for(int x = 0; x <200; x++){
    loadvalue = analogRead(A0);
    average = (loadvalue + average)/2;
    delay(1);
  }
  Serial.println(average,4);
  return average;
}
    
    
