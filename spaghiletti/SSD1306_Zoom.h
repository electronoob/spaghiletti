/* SSD1306 AVR ZoomyZoomZoom Driver */

#include <avr/power.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#ifndef F_CPU
#define F_CPU 16000000
#endif
#include <util/delay.h>
#define PIN_DC    5
#define PIN_RESET 6
#define PIN_SDIN  7
#define PIN_SCLK  3
/* I used PORTD for these connections which is hard coded. */

#define RST_OLED PORTD = 0x00;  _delay_us(10); PORTD = (1 << PIN_RESET);

void oledStart();
void oledWriteString(char *characters);
void oledWriteCharacter(char character);
void oledWriteData(uint8_t data);
void oledWriteCmd(uint8_t command);
void oledWipeScreen();
