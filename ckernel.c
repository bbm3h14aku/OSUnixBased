/********************************************************************** 
 * 
 * 
 *
 *
 * 
 *
 *
 *
 **********************************************************************/
#include "os.h"
#include "datatyps.h"
void menu(int choice);
void calc(int x, int y, char opcode);
void userLogn();
void initOs();
int isLgn = 0;
int ext = 0;
void initOs()
{
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	timmer_install();
	keyboard_install();
	//TODO: Andere Basis Funktionen aus PrettyOS nach Coden
}
int userLogn()
{
	
}
int main(void)
{
	initOs();
	userLogn();
	if(isLgn == 1)
	{
		kprintf("*************************************************", A, 1);
		kprintf("*\t\t WELCOME TO bib OS \t\t *", A, 1);
		kprintf("*\t\t Copyright (c) 2016 Paul & Jan \t\t*", A, 1);
		kprintf("*************************************************", A, 1);
	}
	return 0;
}

