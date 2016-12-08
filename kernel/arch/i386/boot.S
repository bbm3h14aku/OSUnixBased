# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	# Call the global constructors.
	call _init

	call pm
	
	call hl
	#Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
hl:	
	jmp hl

###########
## Calls ##
###########

empty_8042:
    call Waitingloop
    inb $0x64, %al
    cmp $0xff, %al		# ... no real kbc at all?
    je .done_empty_8042
   
    test $1, %al		# something in input buffer?
    jz .no_output
    call Waitingloop
    inb $0x60, %al		# yes: read buffer
    jmp empty_8042		# and try again
   
.no_output:
    test $2, %al		# command buffer empty?
    jnz empty_8042		#no: we can't send anything new till it's empty
.done_empty_8042:
ret

print_string:
    movb $0x0E, %ah 
.loop_print_string:
    lodsb				#grab a byte from SI
    test %al, %al		#test AL
    jz .done_print_string			#if the result is zero, get out
    int $0x10			#otherwise, print out the character!
    jmp .loop_print_string
.done_print_string:
    ret

clrscr:
    movw $0x0600, %ax
    xor %cx, %cx
    movw $0x174F, %dx
    movb $0x07, %bh 
    int $0x10
    ret

Waitingloop:                   
    movl $0x9FFFF, %ebx
.loop_Waitingloop:
    dec %ebx     
    jnz .loop_Waitingloop
    ret 


###################################
## Global Descriptor Table (GDT) ##
###################################

NULL_Desc:
    .long    0
    .long    0
   
CODE_Desc:
    .word    0xFFFF		# segment length  bits 0-15 ("limit")    
    .word    0				# segment base    byte 0,1      
    .byte    0				# segment base    byte 2    
    .byte    0b10011010     # access rights
    .byte    0b11001111     # bit 7-4: 4 flag bits:  granularity, default operation size bit, 2 bits available for OS
                        # bit 3-0: segment length bits 16-19 
    .byte    0             # segment base    byte 3    

DATA_Desc:
    .word    0xFFFF        # segment length  bits 0-15
    .word    0             # segment base    byte 0,1
    .byte    0             # segment base    byte 2
    .byte    0b10010010     # access rights
    .byte    0b11001111     # bit 7-4: 4 flag bits:  granularity, big bit (0=USE16-Segm., 1=USE32-Segm.), 2 bits avail.
                        # bit 3-0: segment length bits 16-19
    .byte    0             # segment base    byte 3       

gdtr:
	Limit:
    	.word 24          # length of GDT
	Base:    	
		.long NULL_Desc   # base of GDT ( linear address: RM Offset + Seg<<4 )*/

###################################
##    switch to protectedmode    ##
###################################

pm:
	call clrscr
    mov msg_pm, %si
    call print_string
    #call Waitingloop
	ret
/*
    cli               ; clear interrupts

    lgdt [gdtr]       ; load GDT via GDTR (defined in file "gtd.inc")

; we actually only need to do this ONCE, but for now it doesn't hurt to do this more often when
; switching between RM and PM
    in  al, 0x92      ; switch A20 gate via fast A20 port 92
    cmp al, 0xff      ; if it reads 0xFF, nothing's implemented on this port
    je .no_fast_A20
   
    or  al, 2         ; set A20_Gate_Bit (bit 1)
    and al, ~1        ; clear INIT_NOW bit (don't reset pc...)
    out 0x92, al
    jmp .A20_done
   
.no_fast_A20:         ; no fast shortcut -> use the slow kbc...
    call empty_8042  
   
    mov al, 0xD1      ; kbc command: write to output port
    out 0x64, al
    call empty_8042
   
    mov al, 0xDF      ; writing this to kbc output port enables A20
    out 0x60, al
    call empty_8042

.A20_done:
    mov eax, cr0      ; switch-over to Protected Mode
    or  eax, 1        ; set bit 0 of CR0 register
    mov cr0, eax      ;

    jmp 0x8:ProtectedMode*/


msg_pm:
.ascii "Test"

.size _start, . - _start

