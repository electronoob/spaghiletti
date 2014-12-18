#include "spaghiletti.h"
#include "SSD1306_Zoom.h"

int main(void)
{
	oledStart();
	while(1)
	{
		oledWriteCmd(0xb0);
		oledWriteCmd(0x00);
		oledWriteCmd(0x10);
		oledWriteString("TODO:");
		oledWriteCmd(0xb1);
		oledWriteCmd(0x00);
		oledWriteCmd(0x10);
		oledWriteString("* FR sync signal, prevents tearing effect.");

		oledWriteCmd(0xb3);
		oledWriteCmd(0x00);
		oledWriteCmd(0x10);
		oledWriteString("* Improve line wrapping.");

		oledWriteCmd(0xb7);
		oledWriteCmd(0x00);
		oledWriteCmd(0x10);
		oledWriteString("electronoob.com");
		while(1);
	}
}
