#include <sys/util.h>
#include <sys/system.h>
#include "header/irq.h"

void * irq_routines[16] = { 0 };

void irq_install_handler(int irq, void (*handler)(struct regs* r))
{
	irq_routines[irq] = handler;
}

void irq_unistall_handler(int irq)
{
	irq_routines[irq] = 0;
}

void irq_remap()
{
	//Start init Sequenz
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);

	//Definiere PIC Vektoren
	outportb(0x21, 0x20);	//Setze Offset Master PIC auf 0x20(32): Eintrag 32-39
	outportb(0xA1, 0x28);	//Setze Offset Slave PIC auf 0x28(40): Eintrag 40 - 47

	//Fortsetzung init Seq.
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);

	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);

	outportb(0x21, 0x00);
	outportb(0xA1, 0x00);
}

void irq_install()
{
	irq_remap();
	idt_set_gate(32, (unsigned) _irq0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned) _irq1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned) _irq2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned) _irq3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned) _irq4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned) _irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned) _irq6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned) _irq7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned) _irq8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned) _irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned) _irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned) _irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned) _irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned) _irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned) _irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned) _irq15, 0x08, 0x8E);
}

void _irq_handler(struct regs* r)
{
	//Funktions pointer
	void (*handler)(struct regs* r);
	//Prüfen auf spezifischen Handler um IRQ zu starten
	handler = irq_routines[r->int_no - 32];
	//Prüfe auf
	if(handler)
	{
		handler(r);
	}
	if(r->int_no >= 40)
	{
		outportb(0xA0, 0x20);
	}
	outportb(0x20, 0x20);
}
