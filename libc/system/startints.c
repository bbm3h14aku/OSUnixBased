#include <sys/util.h>

inline void startints()
{
	asm volatile ("sti");
}
