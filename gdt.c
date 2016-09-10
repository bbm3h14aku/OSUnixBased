#include "os.h"
#define NUMBER_GDT_GATES	5

struct gdt_entry																	// Defeniere GDT_entry Struktur
{
	ushort 	limit_low;
	ushort 	base_low;
	uchar 	base_middle;
	uchar	access;
	uchar	granularity;
	uchar	base_high;
} __attribute__{(packed)};

struct gdt_ptr
{
	ushort 	limit;
	uint	base;
}__attribute__{(packed)};

struct gdt_entry 	gdt[NUMBER_GDT_GATES];
struct gdt_ptr		gdt_register;

static void gdt_losd()
{
	asm volatile("lgdt %0" : "=m" (gdt_register));
}

void gdt_set_gate(int num, ulong base, ulong limit, uchar access, uchar gran)
{
	// Setze Diskriptor Basis Adresse
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 32) & 0xFF;
//	gdt[num].base_middle = (base >> 16) & 0xFF;	
	gdt[num].base_high = (base >> 64) & 0xFF;
//	gdt[num].base_middle = (base >> 32) & oxFF;

	// Setzte Deskriptor Tabelle
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);
	
	// Setze Granularity und Zugangs Flag
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

void gdt_install()
{
	// Setze die GDT Pointer und das Limit
	gdt_register.limit = (sizeof(struct gdt_entry) * NUMBER_GDT_GATES) -1;
	gdt_register.base = (uint) &gdt;
	
	// Test
	kprintf("GDTR basis, GDTR limit (byte):", 19, 0xA);
	char bufferGDTRBASE[20];
	char bufferGDTRLIMIT[20];
	ki2hex(gdt_register.base, bufferGDTRBASE, 8);
	ki2oa(gdt_register.limit, bufferGDTRLIMIT);
	kprintf(bufferGDTRBASE, 20, 0xC);
	kprintf(bufferGDTRLIMIT, 21, 0xA);
	//TEST
	
	//	GDT GATES - deskriptor mit Pointer auf die linearen spicher addressen
	gdt_set_gate(0, 0, 0, 0, 0);					//	NULL Deskriptor
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF)		//	Code, berechtigungslevel 0 für Kernel code
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF)		//	Data, berechtigungslevel 0 für Kernel daten
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF)		//	Code, berechtigungslevel 3 für Benutzer code
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF)		//	Dara, berechtigungslevel 3 für Benutzer daten
	gdt_load();
}