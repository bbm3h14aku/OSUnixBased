#include "header/os.h"

void initOs();

int isLgn = 0;
int ext = 0;

void initOs()
{
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	timer_install();
	keyboard_install();
}

int main()
{
	initOs();
	userLogn();
	kprintf("*************************************************", 0xA, 1);
	kprintf("*\t\t WELCOME TO Moonshine Kernel\t\t *", 0xA, 2);
	kprintf("*\t\t Copyright (c) 2016 Paul & Jan\t\t*", 0xA, 3);
	kprintf("*************************************************", 0xA, 4);
	return 0;
}
