#include <limits.h>

int kpower(int base, int n)
{
	int i, p;
	if(n == 0)
		return 1;
	p=1;
	for(i = 1; i <=n; ++i)
		p = p * base;
	return p;
}
