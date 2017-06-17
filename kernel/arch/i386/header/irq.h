#ifndef _IRQ_KERNEL_H
#define _IRQ_KERNEL_H

void _irq0();
void _irq1();
void _irq2();
void _irq3();
void _irq4();
void _irq5();
void _irq6();
void _irq7();
void _irq8();
void _irq9();
void _irq10();
void _irq11();
void _irq12();
void _irq13();
void _irq14();
void _irq15();


void _irq_handler();
void irq_install_handler(int, void(*handler)(struct regs* r));
void irq_unistall_handler(int);
void irq_remap();
void irq_install();
#endif