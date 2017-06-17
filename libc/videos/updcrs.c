#include <video.h>
#include <sys/util.h>

void updcrs(int row, int col)
{
	unsigned short position = (row * 80) + col;

	//Cursor HighPort in vga Index Register
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (unsigned char) ((position>>8)&0xFF));

	//Cursor LowPort in vga Register
	outportb(0x3D4, 0xF);
	outportb(0x3D5, (unsigned short)(position & 0xFF));
}
