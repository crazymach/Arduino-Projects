/*
 Rainbowduino v3.0

 Scrolling text

*/

#include <Rainbowduino.h>

String message = "HAPPY VETERANS DAY";

void setup()
{
  Rb.init();
}

unsigned char x,y,z;

void scroll_text(String msg)
{
    int len = msg.length();
    const int kern = 6;
    byte msg_b[len+1];
    msg.getBytes(msg_b, len+1);

    for (int i = 0; i <= len * kern ; i++) {
        for (int b = 0 ; b < len ; b++) {
            if ((b * kern) > ( i - kern) && (b * kern) < (i + kern) ) {
                Rb.drawChar(msg_b[b],- i + (b * kern),1,random(0xFFFFFF));
            }
        }
        delay(50);
        Rb.blankDisplay();
    }
}

void loop()
{

    scroll_text(message);

}
