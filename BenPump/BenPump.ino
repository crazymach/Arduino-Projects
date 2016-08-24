int LED_CONTROL_PIN=3;
int inPin=7;
int val = 0;
long previousMillis = 0;        // will store last time LED was updated
int STATE=0;
#define PUMP 1;
#define STAY_IDLE 2;

long PUMP_interval =10000;
long IDLE_interval =60000*30;
void ACTION_PUMP(void);
void ACTION_IDLE(void);

void setup(){
  Serial.begin(9600);
  pinMode(LED_CONTROL_PIN, OUTPUT);
}

void loop(){
  unsigned long currentMillis=millis();

  
  switch (STATE){
    case 1:
       if (currentMillis-previousMillis>PUMP_interval){
         previousMillis=currentMillis;
         STATE=STAY_IDLE;
       }
       ACTION_PUMP();
       Serial.println("PUMP");
    break;
    case 2:
      val = digitalRead(inPin);
  if (val == HIGH) {
    previousMillis=currentMillis;
    STATE=PUMP;
  } else {
    STATE=STAY_IDLE;
  }
    
    
       if(currentMillis-previousMillis>IDLE_interval){
         previousMillis=currentMillis;
         STATE=PUMP;
       }
       ACTION_IDLE();
       Serial.println("IDLE");
    break;
    default:
    STATE=STAY_IDLE;
  }
  
}

void ACTION_PUMP(void){
    digitalWrite(LED_CONTROL_PIN, HIGH);
}
void ACTION_IDLE(void){
    digitalWrite(LED_CONTROL_PIN, LOW);
}

