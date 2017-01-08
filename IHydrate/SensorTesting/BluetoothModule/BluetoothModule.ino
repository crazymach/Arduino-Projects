
char INBYTE;

int LED = 12;               //Digital Output LED pin

float analogValueAverage = 0;

float loadMin = 2; // kg
int AnalogValMin = 300; // analog reading taken with load A on the load cell

float loadMax = 4; // kg
int AnalogValMax = 800; // analog reading taken with load B on the load cell

long time = 0; //
int timeBetweenReadings = 50; // We want a reading every 200 ms;

int NoLoad = .9;

void setup(){
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop(){
  int AnalogLoadSensor = analogRead(A0);  //analog reading pin

  analogValueAverage = 0.99*analogValueAverage + 0.01*AnalogLoadSensor;
  if(millis() > time + timeBetweenReadings){
  
    float loadreading = analogToLoad(analogValueAverage);
    INBYTE = Serial.read();
    if(loadreading > .8) {
      Serial.print("Weight reading");
      Serial.println(loadreading,5);
    }
    else if(INBYTE == '1') {
      Serial.println(loadreading,5);
      blinking();
    }
  
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


float analogToLoad(float analogval){		//taking in value
  float load = mapfloat(analogval, AnalogValMin, AnalogValMax, loadMin, loadMax);
  return load;
}

float mapfloat(float analogval, float AnalogValMin, float AnalogValMax, float loadMin, float loadMax)//equation for mapping float values
{
  return (analogval - AnalogValMin) * (loadMax - loadMin) / (AnalogValMax - AnalogValMin) + loadMin;
}





