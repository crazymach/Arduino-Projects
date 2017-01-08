int count = 0;
int EN;
void setup() {
  Serial.begin(9600);
  
}

void loop(){
  sensor();
  

  
  
}

void sensor(){
    int analogPin1 = analogRead(A0);
    int analogPin2 = analogRead(A1);
    if (analogPin1 < 250)
     { 
       EN == 1;
       Serial.print("before");
       Serial.println(EN);
       

     }
    if (analogPin2 < 250 )
     {
       count += 1;
       EN == 0;
       Serial.print("after");
       Serial.println(EN);
       Serial.println(count);

     }

}

