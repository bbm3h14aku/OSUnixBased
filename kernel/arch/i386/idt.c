#include "header/idt.h"

// Deklarirer 256 Einträge und Pointer
struct idt_entry idt[256];
struct idt_ptr idt_register;

static void idt_load()
{
	asm volatile ("lidt %0" : "=m" (idt_register));
	// lade IDT Einträge ins register
}

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
	idt[num].base_lo = (base		& 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;
	idt[num].sel	 = sel;
	idt[num].always0 = 0;
	idt[num].flags 	 = flags;
}

void idt_install()
{
	// Pointer setzen
	idt_register.limit = (sizeof(struct idt_entry) * 256)-1;
	idt_register.base  = (unsigned int) &idt;
	memset(&idt, 0, sizeof(struct idt_entry) * 256);
	//IDT register zeigt auf IDT
	idt_load();
}
