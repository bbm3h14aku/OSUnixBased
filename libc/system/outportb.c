#include <sys/util.h>

inline void outportb(unsigned port, unsigned val)
{
	asm volatile("outb %%al, %%dx" : : "a"(val), "d"(port));
}
