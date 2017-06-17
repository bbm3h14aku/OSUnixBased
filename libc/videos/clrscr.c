#include <video.h>

void clrscr()
{
	unsigned long* vidmem = (unsigned long*) 0xb8000;
	unsigned long i = 0;
	while(i < (40*25))
	{
		vidmem[i] = 0x0A20A20;
		++i;
	}
}
