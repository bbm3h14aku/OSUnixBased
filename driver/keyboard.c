/*
 * Tastaturtreiber
 *	Version 0.1a vom 29/04/2016
 *  by Jan - Frederic Kurzweil
 * Funktionsumfang
 * - keyboard_init
 * 		leerlauf, falls der Puffer leer sein sollte
 * - FetchAndAnalyzeScancode
 *		Analyse des Scancode, es wird geprüft ob die Shift Tate
 *		gedrückt wurde und gibt dann den richtigen ASCII code zuürck um das Zeichen darstellen zukönnen
 * - kgetch
 * 		öffentliche Funktion zum einlesen von zeichen von der Tastatur es wird ein ASCII Code zurück gegeben
 * - keyboard_handler
 * 		testhandler um zu prüfen ob Tastatur eingaben erkannt und korrekt verarbeitet werden
 * - keyboard_install //TODO: herraus finden was der genau wo rein installiert wird
 */

#include "lokals/deDE.h"
#include "../header/os.h"

int ShiftKeyDown;															// Variable für ShiftKeyDown

void keyboard_init()														// Warte falls der Puffer leer ist
{
	while (inportb(0x64) & 1)
		inportb(0x60);
}

unsigned int FetchScancode()
{
	// Port 0x60 Scancode von Tastatur  lesen
	return ( inportb(0x60));
}

unsigned int FetchAndAnalyzeScancode()
{
	unsigned int scancode;															// tastatur scancode
	while(TRUE)																// Schleife nach dem eine (w/o shift key) Taste gedrückt wurde
	{
		while( !(inportb(0x60)&1)); // 0x60 lese scancode von der Tastatur
		scancode = FetchScancode();
		if( scancode & 0x80 )												// Wurde die Taste los gelassen ? prüfe Bit 7 (100000000b = 0x80) des scancodes
		{
			scancode &= 0x7F;												// Taste wurde losgelassen, verarbeite nur die 7 low bits (01111111b = 0x7F)
			if(scancode == KRLEFT_SHIFT || scancode == KRRIGHT_SHIFT)		// prüfe ob shift gedrückt
			{
				ShiftKeyDown = 0;
				// Nein Shift wurde nicht gedrückt --> NonShift
				continue;
			}
		}
		if ( scancode == KRLEFT_SHIFT || KRRIGHT_SHIFT )				// erfasse scancode der shift taste, falls diese gedrückt wurde
		{
			ShiftKeyDown = 1;											// Falls die taste gedrückt wurde, benutze die asciiShift Zeichen
			continue;													// schleife damit nicht der scancode oder shift taste zurück gegeben wird
		}
		// verlasse die schleife
		return scancode;
	}
}

unsigned char const kgetch()													// Scancode --> ASCII
{
	unsigned int scan;																// Scancode von der Tastatur
	unsigned char retchar;															// retchar --> rückgabe wert des scnacode als ASCII Code
	scan = FetchAndAnalyzeScancode();										// hol den scancode und analysiere ob Shift gedrückt wurde
	if(ShiftKeyDown)
		retchar = asciiShift[scan];											// gedrückter ShiftCode
	else
		retchar = asciiNonShift[scan];										// nichtgedrückter ShiftCode
	return retchar;															// ASCII Version
}

void keyboard_handler(struct regs* r)
{
	uchar bufferKey[10];
	bufferKey[0] = kgetch();
}

void keyboard_install()														// Installiere den "Keyboard_Handler" in irq1
{
	irq_install_handler(1, keyboard_handler);
	keyboard_init();
}
