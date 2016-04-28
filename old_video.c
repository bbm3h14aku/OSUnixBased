/* Jan - Frederic Kurzweil (c) 2016
 * C-Kernel Source Version 1
 * Routinen zum darstellen von Content und zum leeren
 * void k_clear_screen()
 * Videospeicher Array = vidmem = 4000 = 2*80*25 Byte (80 Spalten * 25 Zeilen)
 */
 
 void k_clear_screen()
 {
	char* vidmem = (char*) 0xb8000;
	unsigned int i=0;
	while(i<(80*2*25))
	{
		vidmem[i] = 0x20; //ASCII: 0x20 Space 
		++i;
		vidmem[i] = 0x07; //ASCII: Schwarz auf Weiß
		++i;
	};		
 };
 
 void k_clear_screen_16()
 {
	unsigned int* vidmem = (unsigned int*) 0xb8000;
	unsigned int i = 0;
	while(i<(80*25))
	{
		vidmem[i] = 0x0720;
		++i;
	};
 };
 
 void k_clear_screen_32()
 {
	unsigned long* vidmem = (unsigned long*) 0xb8000;
	unsigned long i = 0;
	while(i<(40*25))
	{
		vidmem[i] = 0x07200720;
		++i;
	};
 };
 
 unsigned int k_printf(char* message, unsigned int line)
 {
	char* vidmem = (char*) 0xb8000;
	unsigned  int i = line * 80 * 2;
	while(*message != 0)
	{
		if(*message == 0x2f)
		{
			*message++;
			if(*message == 0x6e)
			{
				line++;
				i = (line * 80 * 2);
				*message++;
				if(*message == 0)
				{
					return 1;
				};
			};
		};
		vidmem[i] = *message;
		*message++;
		++i;
		vidmem[i] = 0x7;
		++i;
	};
	return 1;
 };
 
 unsigned int e_printf(char *message, unsigned int line)
 {
	char *vidmem = (char*) 0xb8000;
	unsigned int i = (line * 80 * 2);
	
	while(*message != 0)
	{
		if(*message == '\n' )
		{
			line++;
			i = (line * 80 * 2);
			*message++;
		}
		else
		{
			vidmem[i] = *message;
			*message++;
			++i;
			vidmem[i] = 0x7;
			++i;
		};
	};
	return 1;
 };