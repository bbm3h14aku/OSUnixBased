#ifndef _ISRS_H
#define _ISRS_H

#include <stdio.h>
#include <register.h>

// Funktions Prototypen aller Exception Handler Ersten 32 Einträge im IDT sind reserviert und designed für Service Exception
 void _isr0();
 void _isr1();
 void _isr2();
 void _isr3();
 void _isr4();
 void _isr5();
 void _isr6();
 void _isr7();
 void _isr8();
 void _isr9();
 void _isr10();
 void _isr11();
 void _isr12();
 void _isr13();
 void _isr14();
 void _isr15();
 void _isr16();
 void _isr17();
 void _isr18();
 void _isr19();
 void _isr20();
 void _isr21();
 void _isr22();
 void _isr23();
 void _isr24();
 void _isr25();
 void _isr26();
 void _isr27();
 void _isr28();
 void _isr29();
 void _isr30();
 void _isr31();

void _fault_handler(struct regs*);
void isrs_install();

#endif
