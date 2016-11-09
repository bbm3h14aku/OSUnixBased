all:
	nasm -f bin boot.asm -o boot.bin
	nasm -f aout kernel.asm -o kernel.o
	nasm -f aout isr.asm -o isr.o
	
	gcc -m32 -Wall -O -c kernel.c -o ckernel.o -O1
	gcc -m32 -Wall -O -c video.c -o video.o -O1
	gcc -m32 -Wall -O -c math.c -o math.o -O1
	gcc -m32 -Wall -O -c util.c -o util.o -O1
	gcc -m32 -Wall -O -c gdt.c -o gdt.o -O1
	gcc -m32 -Wall -O -c idt.c -o idt.o -O1
	gcc -m32 -Wall -O  -c isrs.c -o isrs.o	
	gcc -m32 -Wall -O  -c irq.c -o irq.o
	gcc -m32 -Wall -O  -c timer.c -o timer.o
	gcc -m32 -Wall -O  -c keyboard.c -o keyboard.o
	ld -m elf_i386 -T kernel.ld kernel.o isr.o ckernel.o video.o gdt.o idt.o isrs.o irq.o util.o math.o timer.o keyboard.o -o ckernel.bin --verbose
	
	echo boot.bin ckernel.bin > moonix
	
	rm *.o
	rn *.bin
	mv moonix moonix.bin
	
	DOS
	partcopy moonix.bin 0 2800 -f0
	
	UNIX
	dd if=moonix.bin of=~/cd_image.iso
	
	CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -fstrength-reduce -fomit-frame-pointer -finline-functions
