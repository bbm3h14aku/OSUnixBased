all:
	nasm -O32 -f bin boot.asm -o boot.bin
	nasm -O32 -f aout kernel.asm -o kernel.o
	nasm -O32 -f aout isr.asm -o isr.o
	
	gcc -Wall -O -c kernel.c -o ckernel.o -O1
	gcc -Wall -O -c driver/video.c -o video.o -O1
	gcc -Wall -O -c math.c -o math.o -O1
	gcc -Wall -O -c util.c -o util.o -O1
	gcc -Wall -O -c gdt.c -o gdt.o -O1
	gcc -Wall -O -c idt.c -o idt.o -O1
	gcc  -Wall -O  -c isrs.c -o isrs.o	
	gcc  -Wall -O  -c irq.c -o irq.o
	gcc  -Wall -O  -c timer.c -o timer.o 	
	gcc  -Wall -O  -c driver/keyboard.c -o keyboard.o
	ld -T kernel.ld kernel.o isr.o ckernel.o video.o gdt.o idt.o isrs.o irq.o util.o math.o timer.o keyboard.o -o ckernel.bin --verbose
	
	echo boot.bin ckernel.bin > moonix
	
	rm *.o
	rn *.bin
	mv moonix moonix.bin
	
	DOS
	partcopy moonix.bin 0 2800 -f0
	
	UNIX
	dd if=moonix.bin of=~/cd_image.iseide
	
	CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -fstrength-reduce -fomit-frame-pointer -finline-functions