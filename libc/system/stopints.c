#include <sys/util.h>

inline void stopints()
{
	asm ("cli");
}
