/*
 * VideoTreiber
 * Version 0.1a vom 29/04/2016
 * by Jan - Frederic Kurzweil
 * Funktionsumfang
 * - kclrscr()
 * 		leert den screen
 * - kprintf(nachricht, zeile, attribut)
 * 		gibt eine nachricht aus das erste attribut bezeichnet die nachricht selbst
 *		das zweite Attribut bezeichnet die zeile
 *		das dritte Attribut bezeichnet das Attribut für die Nachricht z.b die farbe der Ausgabe
 * - upcrs(zeile, spalte)
 *		setzt den cursor an die gewünschte position
 */
#include "../header/os.h"

void kclrscr()
{
	unsigned long* vidmem = (unsigned long*) 0xb8000;
	unsigned long i = 0;
	while(i<(40*25))
	{
		vidmem[i] = 0x0A200A20;
		++i;
	};
}

unsigned int kprintf(char *message, unsigned int line, char attribute)
{
	char* vidmem = (char*) 0xb8000;
	uint i = line * 80 * 2;

	while(*message != 0)
	{
		if(*message == '\n')
		{
			line++;
			i = (line * 80 * 2);
			*message++;
		}
		else
		{
			vidmem[i] = *message;
			*message++;
			++i;
			vidmem[i] = attribute;
			++i;
		}
	};
	return 1;
};

void upcrs(int row, int col)
{
	ushort position = (row * 80) + col;

	//Cursor HIGH Port in vga Index Register
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (unsigned char) ((position>>8)&0xFF));
	// Cursor LOW Port in vga Index Register
	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (unsigned short)(position & 0xFF));
}
