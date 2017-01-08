
// creates a "virtual" serial port/UART
// connect BT module TX tol D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND
void setup()
{
  // set digital pin to control as an output
  pinMode(12, OUTPUT);
  // set the data rate for the SoftwareSerial port
  Serial.begin(9600);
  // Send test message to other device
  Serial.println("Hello from Arduino");
}
char a; // stores incoming character from other device
void loop()
{
    // if text arrived in from BT serial...
  {
    a = (Serial.read());
    if (a == '1')
    {
      digitalWrite(12, HIGH);
      Serial.println("LED on");
    }
    if (a == '2')
    {
      digitalWrite(12, LOW);
      Serial.println("LED off");
    }
    if (a == '?')
    {
      Serial.println("Send '1' to turn LED on");
      Serial.println("Send '2' to turn LED on");
    }
    // you can add more "if" statements with other characters to add more commands
  }
}
