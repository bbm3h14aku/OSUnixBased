#ifndef IDT_H
#define IDT_H

// IDT Eintrag
#include <string.h>
struct idt_entry
{
	unsigned short base_lo;
	unsigned short sel;
	unsigned char always0;
	unsigned char flags;
	unsigned char base_hi;
}__attribute__((packed));

//IDT Ptr
struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed));

void idt_install();
static void idt_load();
void idt_set_gate(unsigned char, unsigned long, unsigned short, unsigned char);

#endif
