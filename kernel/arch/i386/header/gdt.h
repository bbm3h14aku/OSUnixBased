#ifndef _GDT_KERNEL_H
#define _GDT_KERNEL_H

#define NUMBER_GDT_GATES 5

// GDT Entry as Struct
struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granuarity;
	unsigned char base_high;
}__attribute__((packed));

struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed));

// GDT Entries plus special gdt pointer
struct gdt_entry gdt[NUMBER_GDT_GATES];
struct gdt_ptr gdt_register;

static void gdt_load();
void gdt_set_gate();
void gdt_install();

#endif