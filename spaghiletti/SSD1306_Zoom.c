#include "SSD1306_Zoom.h"
#include "font.h"

void oledStart()
{
	clock_prescale_set(clock_div_1);
	DDRD = 0xff;
	PORTD = 0x00;
	RST_OLED;
	oledWriteCmd(0x8d); //enable charge pump
	oledWriteCmd(0x14);
	//  oledWriteCmd(0xa8); //set MUX ratio
	//  oledWriteCmd(0x3f);
	oledWriteCmd(0xd3); //set display offset
	oledWriteCmd(0x00);
	oledWriteCmd(0x40); //set display start line
	//oledWriteCmd(0xa1); //set segment re-map (horizontal flip) - reset value is 0xa0 (or 0xa1)
	//oledWriteCmd(0xc8); //set COM output scan direction (vertical flip) - reset value is 0xc0 (or 0xc8)
	oledWriteCmd(0xda); //set COM pins hardware configuration
	oledWriteCmd(0x12); //reset value is 0x12
	oledWriteCmd(0x81); //set contrast (2-byte)
	oledWriteCmd(0xff); //was ff
	oledWriteCmd(0xa4); //disable entire display on
	oledWriteCmd(0xa6); //set normal display
	//  oledWriteCmd(0xd5); //set oscillator frequency
	//  oledWriteCmd(0x80);
	//  oledWriteCmd(0xdb); //vcomh deselect level (brightness)
	//  oledWriteCmd(0x20);
	oledWriteCmd(0x20); //set horizontal addressing mode for screen clear
	oledWriteCmd(0x01);
	oledWriteCmd(0x21); //set column start and end address
	oledWriteCmd(0x00); //set column start address
	oledWriteCmd(0x7f); //set column end address
	oledWriteCmd(0x22); //set row start and end address
	oledWriteCmd(0x00); //set row start address
	oledWriteCmd(0x07); //set row end address
	oledWriteCmd(0xaf); //set display on
	oledWipeScreen();
	oledWriteCmd(0x20); //set page addressing mode
	oledWriteCmd(0x02);
	oledWriteCmd(0xb7); //set page start address to page 7
	oledWriteCmd(0x00); //set lower column start address
	oledWriteCmd(0x10); //set upper column start address
	//  oledWriteCmd(0x27); //set right horizontal scroll
	//  oledWriteCmd(0x0);  //dummy byte
	//  oledWriteCmd(0x0);  //page start address
	//  oledWriteCmd(0x7);  //scroll speed
	//  oledWriteCmd(0x7);  //page end address
	//  oledWriteCmd(0x0);  //dummy byte
	//  oledWriteCmd(0xff); //dummy byte
	//  oledWriteCmd(0x2f); //start scrolling
	oledWriteCmd(0xb0); //set page start address to page 0
}
void oledWriteString(char *characters)
{
	while (*characters) oledWriteCharacter(*characters++);
}
void oledWriteCharacter(char character)
{
	for (int i=0; i<5; i++)
	oledWriteData(pgm_read_byte(&ASCII[character - 0x20][i]));
	oledWriteData(0x00);
}
void oledWriteCmd(uint8_t command)
{
	PORTD &= ~_BV(PIN_DC);
	int i;
	for (i = 0; i<8; i++){
		if((command & _BV(7)) == _BV(7)) {
			PORTD |= _BV(PIN_SDIN);
			} else {
			PORTD &= ~_BV(PIN_SDIN);
		}
		PORTD |= _BV(PIN_SCLK);
		PORTD &= ~_BV(PIN_SCLK);
		command = command << 1;
	}
}
void oledWriteData(uint8_t data)
{
	PORTD |= _BV(PIN_DC);
	int i;
	for (i = 0; i<8; i++){
		if((data & _BV(7)) == _BV(7)) {
			PORTD |= _BV(PIN_SDIN);
			} else {
			PORTD &= ~_BV(PIN_SDIN);
		}
		PORTD |= _BV(PIN_SCLK);
		PORTD &= ~_BV(PIN_SCLK);
		data = data << 1;
	}
}
void oledWipeScreen()
{
	PORTD |= _BV(PIN_DC);
	for(int k = 0; k < 1024; k++)
	for (int i = 0; i<8; i++){
		PORTD &= ~_BV(PIN_SDIN);
		PORTD |= _BV(PIN_SCLK);
		PORTD &= ~_BV(PIN_SCLK);
	}
}