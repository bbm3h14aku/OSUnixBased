#include <stdio.h>
#include <sys/util.h>
#include "keyboard_enEN.h"

int ShiftKeyDown;
unsigned int FetchAndAnalyzeScancode();

unsigned char getchar()
{
	unsigned int scan;
	unsigned char retchar;
	scan = FetchAndAnalyzeScancode();
	if(ShiftKeyDown)
		retchar = asciiShift[scan];
	else
		retchar = asciiNonShift[scan];
	return retchar;
}

unsigned int FetchAndAnalyzeScancode()
{
	unsigned int scancode;
	while(1)
	{
		scancode = inportb(0x60);
		if(scancode & 0x80)
		{
			scancode &= 0x7F;
			if(scancode == RLEFT_SHIFT  || RRIGHT_SHIFT)
			{
				ShiftKeyDown = 0;
			}
		}
		else
		{
			if(scancode == RLEFT_SHIFT  || RRIGHT_SHIFT)
			{
				ShiftKeyDown = 1;
				continue;
			}
		}
		break;
	}
	return scancode;
}
