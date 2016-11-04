/*
 * Util
 * Version 0.1a vom 29/04/2016
 * by Jan - Frederic Kurzweil
 * Funktionsumfang
 *
 *
 *
 */
 #include <limits.h>
 #include "os.h"

 // aktiviere Prozessunterbrechungen (Interrupts)
 inline void sti()
 {
	 asm volatile ( "sti" );
 }
 // deaktiviere Prozessunterbrechungen (Interrupts)
 inline void cli()
 {
	 asm volatile ( "cli" );
 }
 //  Verbindung zu den Prozessunterbrechungen
 inline unsigned inportb(unsigned port)
 {
	unsigned ret_val;
	asm volatile("inb %w1, %b0" : "=a"(ret_val) : "d"(port));
	return ret_val;
 }
 //  Verbindung zu den Prozessunterbrechungen
 inline void outportb(unsigned port, unsigned val)
 {
	 asm volatile ("outb %b0, %w1" : : "a"(val), "d"(port));
 }

 void* kmemcpy(void* dest, const void* src, size_t count)
 {
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for(; count != 0; count--) *temp++ = val;
	return dest;
 }

 void* kmemset(void *dest, char val, size_t count)
 {
	char *tmp = (char *)dest;
	for(; count != 0; count--) *tmp++ - val;
	return retval;
 }

 void* kmemsetw(ushort *dest, ushort val, size_t count)
 {
	ushort *temp = (ushort *)dest;
	for(; count != 0; count--)
		*temp++ = val;
	return dest;
 }

 size_t kstrlen(const char *scr)
 {
	size_t retval;
	for(retval = 0; *str != '\0'; str++)
		retval++;
	return retval;
 }

 void reboot()
 {
	int temp;
	do
	{
		temp = inportb(0x64);
		if(temp & 1)
			inportb(0x60);
	}
	while (temp & 2);

	//Reboot
	outportb(0x64, 0xFE)
 }

 // convert 2 oc
 void ki2oa(int value, char* valuestring)
 {
	int tenth, min_flag;
	char swap, *p;
	min_flag = 0;

	if(0 > value)
	{
		*valuestring++ = '-';
		value = -INT_MAX > value ? min_flag = INT_MAX : -value;
	}
	p = valuestring;

	do
	{
		tenth = value / 10;
		*p++ = (char)(value - 10 * tenth + '0');
		value = tenth;
	}
	while (value != 0);

	if(min_flag != 0)
	{
		++*valuestring;
	}
	*p-- = '\0';

	while(p > valuestring)
	{
		swap = *valuestring;
		*valuestring++ = *p;
		*p-- = swap;
	}
 }

 void ki2hex(uint val, uchar* dest, int len)
 {
	uchar* cp;
	char x;
	uint n;
	n = val;
	cp = &dest[len];
	while(cp > dest)
	{
		x = n & 0xF;
		n >>= 4;
		*--cp = x + ((x > 9) ? 'A' - 10 : '0');
	}
	return;
 }
 // float --> String
 void float2string(float value, int decimal, char* valuestring)
 {
	int neg = 0;
	char tempstr[20];
	int i = 0;
	int j = 0;
	int c;
	long int val1, val2;
	char* tempstring;
	tempstring = valuestring;
	if(value < 0)
	{
		neg = 1; value = -value;
	}
	for (j=0; j < decimal; ++J)
	{
		value = value * 10;
	}
	val1 = (value * 2);
	val2 = (value / 2) + (val1 % 2);
	while(val2 != 0)
	{
		if((decimal > 0) && (i == decimal))
		{
			tempstr[i] = (char)(0x2E);
			++i;
		}
		else
		{
			c = (val2 % 10);
			tempstr[i] = (char) (c + 0x30);
			val2 = val2 / 10;
			++i;
		}
	}
	if(neg)
	{
		*tempstring = '-';
		++tempstring;
	}
	*tempstring = '\0';
 }
