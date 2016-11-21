#include <stdio.h>
#include <video.h>

#include <sys/util.h>
#include <kernel/tty.h>
#include <kernel/color.h>

void printcat()
{
	terminal_writestring("   --              --");
	terminal_writestring("  /  \\____________/  \\");
	terminal_writestring(" (                     )");
	terminal_writestring("(   __           __     )");
	terminal_writestring("(  (__)    __   (__)    )");
	terminal_writestring("(         (  )          )");
	terminal_writestring("(        (    )         )");
	terminal_writestring("(       (______)        )");
	terminal_writestring("(    \\             /    )");
	terminal_writestring("(     \\     |     /     )");
	terminal_writestring("(      \\____|____/      )");

}

void kernel_main(void)
{
	int i = 0;
	terminal_initialize();
	terminal_setcolor(4);
	terminal_writestring("init Keyboard");
	terminal_writestring("Moonshine OS an UNIX Based Operating System\n");
	terminal_writestring("Copyright 2016 St4ck & Sh4d3r\n");
	terminal_setcolor(6);
	printcat();
	terminal_setcolor(1);
	terminal_writestring("");
	terminal_writestring(">> ");
	for(i = 0; i < 15; i++)
		terminal_writecolorstring("TEST", i);
	init_keyboard();
	getchar();
}
