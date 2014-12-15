#include "spaghiletti.h"
#include "SSD1306_Zoom.h"

int main(void)
{
	oledStart();
	while(1)
	{
		  //static unsigned long thisMicros = 0;
		  //static unsigned long lastMicros = 0;
		  oledWriteCmd(0x00); //set lower column start address
		  oledWriteCmd(0x10); //set upper column start address
		  //oledWriteString(dtostrf(thisMicros - lastMicros,8,0,tmp));
		  oledWriteString("electronoob");
		  _delay_ms(1);
		  oledWipeScreen();
		  //_delay_us(10);
		  //lastMicros = thisMicros;
		  //thisMicros = micros(); 
	}
}
