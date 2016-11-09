//OS.h
#ifndef OS_H
#define OS_H

#define TRUE 	1
#define FALSE 	0

#define x86 1

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

// This defines what the stack looks like after an ISR was running
struct regs
{
	unsigned int gs, fs, es, ds;
	unsigned int int_no, err_code;
#ifdef x86
	unsigned int edi, esi, ebp, esp, ebx, ecx, eax;
	unsigned int eip, cs, eflags, userrsp, ss;
#elif
	unsigned int rdi, rsi, rbp, rsp, rbx, rcx, rax;
	unsigned int rip, cs, rflags, userrsp, ss;
#endif
};

extern void kclrscr();
extern unsigned int kprintf(char * message, unsigned int line, char attribute);
extern void upcrs(int row, int col);

extern void keyboard_init();
extern unsigned char const kgetch();
extern char * scanf();
extern unsigned int FetchAndAnalyzeScancode();
extern void keyboard_handler(struct regs* r);

extern void outportb(unsigned port, unsigned val);
inline unsigned inportb(unsigned port);
extern void* kmemset(void *dest, char val, size_t count);
extern unsigned short* kmemsetw(unsigned short *dest, unsigned short val, size_t count);
extern void* kmemcpy(void* dest, const void* src, size_t count);
extern size_t kstrlen(const char *str);
extern void reboot();

extern void cli();
extern void sti();
extern void kitoa(int value, char* valuestring);
extern void ki2hex(unsigned int val, unsigned char* dest, int len);
extern void float2string(float value, int decimal, char* valuestring);

extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdtinstall();

extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

extern void isrs_install();
extern void irq_install();
extern void timer_install();
extern void fault_handler(struct regs* r);
extern void irq_install_handler(int irq, void (*handler)(struct regs* r));
extern void irq_unistall(int irq);
extern void irw_remap(void);
extern void irq_handler(struct regs* r);

extern int kpower(int base, int n);

#endif
