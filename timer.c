#include "header/os.h"

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
	kprintf(bufferTimerticks, 6, 0xB);
	char bufferWaitTicks[20];
	kitoa(eticks, bufferWaitTicks);
	kprintf("           ", 7, 0x0B);
	kprintf(bufferWaitTicks, 7, 0x0B);
}

void timer_wait(unsigned long ticks)
{
	timer_uninstall();
	eticks = ticks;
	timer_install();

	while(eticks)
	{
		kprintf("Wartezeit läuft: ", 8, 0x0B);
	};
	kprintf("Wartezeit vorbei: ", 9, 0x0B);
}

void sleepSeconds(unsigned long seconds)
{
	// Timer ticker Frequenz 18.222 Hz
	timer_wait((unsigned long)18.222 * seconds);
}

void timer_install()
{
	//Timer handler IRQ0
	irq_install(0, timer_handler);
}

void timer_uninstall()
{
	//Uninstall IRQ0
	irq_uninstall_handler(0);
}
