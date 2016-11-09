#include "os.h"

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

static void gdt_load()
{
	asm volatile ("lgdt %0" : "=m" (gdt_register));
}

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
	// Descriptor Basis Adressen
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	//Descriptor Limits
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granuarity = ((limit >> 16) & 0xF);

	//Granularity und Access Flags
	gdt[num].granuarity |= (0xF0);
	gdt[num].access = access;
}

void gdt_install()
{
	//Pointer und Limit vorbereiten
	gdt_register.limit = (sizeof(struct gdt_entry) * NUMBER_GDT_GATES) -1;
	gdt_register.base = (unsigned int) &gdt;

	//TEST
	kprintf("GDTR base, GDTR limit (byte):", 19, 0xA);
	char bufferGDTRBASE[20];
	char bufferGDTRLIMIT[20];
	ki2hex(gdt_register.base, bufferGDTRBASE, 8);
	ki2oa(gdt_register.limit, bufferGDTRLIMIT);
	kprintf(bufferGDTRBASE, 20, 0xC);
	kprintf(bufferGDTRLIMIT, 21, 0xA);

	// GDT Gates - deskriptoren mit Pointer zur lineare speicher adresse
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //Code privilege Lvl 0 = Kernel Code
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data privilege lvl 0 = Kernel Data
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // Code privilege lvl 3 = User
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // Data privilege lvl 3 = user

	gdt_load(); //GDT register (GDTR) der CPU Pointer auf GDT
}
