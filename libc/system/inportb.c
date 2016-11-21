#include <sys/util.h>

inline unsigned inportb(unsigned port)
{
	unsigned ret_val;
	asm volatile ("inb %%dx, %%al" : "=a"(ret_val) : "d"(port));
	return ret_val;
}
