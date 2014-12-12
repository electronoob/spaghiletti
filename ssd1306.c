#define PIN_CS    8
#define PIN_DC    9
#define PIN_RESET 10
#define PIN_SDIN  11
#define PIN_SCLK  12

#include "font.h";

char tmp[8];

void oledWriteString(char *characters)
{
  while (*characters) oledWriteCharacter(*characters++);
}

void oledWriteCharacter(char character)
{
  for (int i=0; i<5; i++) oledWriteData(pgm_read_byte(&ASCII[character - 0x20][i]));
  oledWriteData(0x00);
}

void oledWriteData(byte data)
{
  digitalWrite(PIN_DC, HIGH);
  digitalWrite(PIN_CS, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_CS, HIGH);
}

void oledWriteCmd(byte command)
{
  digitalWrite(PIN_DC, LOW);
  digitalWrite(PIN_CS, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, command);
  digitalWrite(PIN_CS, HIGH);
}

void setup()
{
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_CS, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
//  digitalWrite(PIN_RESET, HIGH);
  digitalWrite(PIN_RESET, LOW);
  delay(1);
  digitalWrite(PIN_RESET, HIGH);
  delay(1);
  
  oledWriteCmd(0x8d); //enable charge pump
  oledWriteCmd(0x14);
  delay(1);
  oledWriteCmd(0xaf); //set display on

//  oledWriteCmd(0xa8); //set MUX ratio
//  oledWriteCmd(0x3f);
  oledWriteCmd(0xd3); //set display offset
  oledWriteCmd(0x00);
  oledWriteCmd(0x40); //set display start line
  oledWriteCmd(0xa1); //set segment re-map (horizontal flip) - reset value is 0xa0 (or 0xa1)
  oledWriteCmd(0xc8); //set COM output scan direction (vertical flip) - reset value is 0xc0 (or 0xc8)
  oledWriteCmd(0xda); //set COM pins hardware configuration
  oledWriteCmd(0x12); //reset value is 0x12
  oledWriteCmd(0x81); //set contrast (2-byte)
  oledWriteCmd(0xff);
//  oledWriteCmd(0xa4); //disable entire display on
//  oledWriteCmd(0xa6); //set normal display
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
  
  
  for (int i=0; i<1024; i++) oledWriteData(0x00); // clear oled screen
  
  oledWriteCmd(0x20); //set page addressing mode
  oledWriteCmd(0x02);
  
  oledWriteCmd(0xb7); //set page start address to page 7
  oledWriteCmd(0x00); //set lower column start address
  oledWriteCmd(0x10); //set upper column start address
  
  oledWriteString("Julian's Code");
  
  
  
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

void loop()
{
  static unsigned long thisMicros = 0;
  static unsigned long lastMicros = 0;
  oledWriteCmd(0x00); //set lower column start address
  oledWriteCmd(0x10); //set upper column start address
  oledWriteString(dtostrf(thisMicros - lastMicros,8,0,tmp));
  lastMicros = thisMicros;
  thisMicros = micros();
//  oledWriteString(" microseconds");
}