#include "os.h"

unsigned long timer_ticks = 0;
unsigned long eticks;

void timer_handler(struct regs* r)
{
	++timer_ticks;
	if(eticks)
		--eticks;

	char bufferTimerticks[20];
	kitoa(timer_ticks, bufferTimerticks);
	kprintf("           ", 6, 0x0B);
}
