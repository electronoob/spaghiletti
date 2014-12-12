
#define PIN_CS    8
#define PIN_DC    9
#define PIN_RESET 10
#define PIN_SDIN  11
#define PIN_SCLK  12
#define HIGH 1
#define LOW 0
#define MSBFIRST 1
#define INPUT 0
#define OUTPUT 1
/* I have not checked enumed val for msbfirst as i will be replacing it anyway */
char tmp[8];

void oledWriteString(char *characters);
void oledWriteCharacter(char character);
void oledWriteData(char data);
void oledWriteCmd(char command);
int main(void);