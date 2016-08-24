//Declarations - set up the variables to be used in the application
byte ledPin[] = {4, 5, 6, 7, 8, 9, 10,11,12,13}; // Create array for LED pins
int potPin = 2; // select the input pin for the potentiometer
int ledDelay; // Set a delay period LED Change
int delayData = 80; // Set a delay period for the data transferred to Excel and attempt to reduce data volumes
int direction = 1;
int currentLED = 0;
int x = 0; //Set the initial counter for LED OUTPUT
int row = 0; // Set the starting Excel row
unsigned long changeTime;
//---------------------------------------------------------------------------------------------------------
// Set up the Arduino Serial port rate, clear all previous data and send the headings for the data transfer to excel
void setup() {
Serial.begin(19200); // opens serial port, sets data rate128000 bps
Serial.println("CLEARDATA"); //clears any residual data
Serial.println("LABEL,Time,Pin,Light Level");
Serial.println("RESETTIMER");
// Reset all pints for the LEDs to digital output

for (int x=0; x<10; x++) { 
pinMode(ledPin[x], OUTPUT); }
changeTime = millis();
}

void loop() {
ledDelay = analogRead(potPin); // read the value from the pot 
if ((millis() - changeTime) > ledDelay) { // if it has been ledDelay ms since last change
changeLED();
changeTime = millis();
}
}
void changeLED() {
for (int x=0; x<10; x++) { // turn off all LED's
digitalWrite(ledPin[x], LOW);
}
digitalWrite(ledPin[currentLED], HIGH); // turn on the current LED
currentLED += direction; // increment by the direction value
// change direction if we reach the end
if (currentLED == 9) {direction = -1;}
if (currentLED == 0) {direction = 1;}

// Send the data to excel and delay the next step for teh set period of time

Serial.print("DATA,TIME,"); Serial.print(currentLED); Serial.print(","); Serial.println(ledDelay);
row++;
x++;
delay (delayData);

}
