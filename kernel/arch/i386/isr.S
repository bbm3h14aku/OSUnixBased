# Interrupt Service Routine isr0 ... isr32
.global _isr0
.global _isr1
.global _isr2
.global _isr3
.global _isr4
.global _isr5
.global _isr6
.global _isr7
.global _isr8
.global _isr9
.global _isr10
.global _isr11
.global _isr12
.global _isr13
.global _isr14
.global _isr15
.global _isr16
.global _isr17
.global _isr18
.global _isr19
.global _isr20
.global _isr21
.global _isr22
.global _isr23
.global _isr24
.global _isr25
.global _isr26
.global _isr27
.global _isr28
.global _isr29
.global _isr30
.global _isr31

.type _isr0, @function
.type _isr1, @function
.type _isr2, @function
.type _isr3, @function
.type _isr4, @function
.type _isr5, @function
.type _isr6, @function
.type _isr7, @function
.type _isr8, @function
.type _isr9, @function
.type _isr10, @function
.type _isr11, @function
.type _isr12, @function
.type _isr13, @function
.type _isr14, @function
.type _isr15, @function
.type _isr16, @function
.type _isr17, @function
.type _isr18, @function
.type _isr19, @function
.type _isr20, @function
.type _isr21, @function
.type _isr22, @function
.type _isr23, @function
.type _isr24, @function
.type _isr25, @function
.type _isr26, @function
.type _isr27, @function
.type _isr28, @function
.type _isr29, @function
.type _isr30, @function
# Divide Zero Exception

_isr0:
	cli
	pushl $0
	pushl $0
	jmp isr_common_stub

# Debug Exception

_isr1:
	cli
	pushl $0
	pushl $1
	jmp isr_common_stub

# Non Maskable Exception

_isr2:
	cli
	pushl $0
	pushl $2
	jmp isr_common_stub

# Int 3 Exception
_isr3:
	cli
	pushl $0
	pushl $3
	jmp isr_common_stub

# Into Exception
_isr4:
	cli
	pushl $0
	pushl $4
	jmp isr_common_stub

# Out of Bounds
_isr5:
	cli
	pushl $0
	pushl $5
	jmp isr_common_stub

# Invalid Opcode Exception
_isr6:
	cli
	pushl $0
	pushl $6
	jmp isr_common_stub

# Coprozessor Not Available Exception
_isr7:
	cli
	pushl $0
	pushl $7
	jmp isr_common_stub

# Double Fault Exception (Mit error code)
_isr8:
	cli
	pushl $0
	pushl $8
	jmp isr_common_stub

# Coprocessor Segement Overrun Exception
_isr9:
	cli
	pushl $0
	pushl $9
	jmp isr_common_stub

# Bad TSS Exception (Mit Error Code)
_isr10:
	cli
	pushl $0
	pushl $10
	jmp isr_common_stub

# Segement not Present Exception
_isr11:
	cli
	pushl $0
	pushl $11
	jmp isr_common_stub

# Stack Fault Exception
_isr12:
	cli
	pushl $0
	pushl $12
	jmp isr_common_stub

# Genreal Protection Fault Exception
_isr13:
	cli
	pushl $0
	pushl $13
	jmp isr_common_stub

# Page Fault Exception
_isr14:
	cli
	pushl $0
	pushl $14
	jmp isr_common_stub

# Rserved Exception
_isr15:
	cli
	pushl $0
	pushl $15
	jmp isr_common_stub

# Rserved Exception
_isr16:
	cli
	pushl $0
	pushl $16
	jmp isr_common_stub

# Rserved Exception
_isr17:
	cli
	pushl $0
	pushl $17
	jmp isr_common_stub

# Rserved Exception
_isr18:
	cli
	pushl $0
	pushl $18
	jmp isr_common_stub

# Rserved Exception
_isr19:
	cli
	pushl $0
	pushl $19
	jmp isr_common_stub

# Rserved Exception
_isr20:
	cli
	pushl $0
	pushl $20
	jmp isr_common_stub

# Rserved Exception
_isr21:
	cli
	pushl $0
	pushl $21
	jmp isr_common_stub

# Rserved Exception
_isr22:
	cli
	pushl $0
	pushl $22
	jmp isr_common_stub

# Rserved Exception
_isr23:
	cli
	pushl $0
	pushl $15
	jmp isr_common_stub

# 24: Reserved
_isr24:
    cli
    pushl $0
    pushl $24
    jmp isr_common_stub

# 25: Reserved
_isr25:
    cli
    pushl $0
    pushl $25
    jmp isr_common_stub

# 26: Reserved
_isr26:
    cli
    pushl $0
    pushl $26
    jmp isr_common_stub

# 27: Reserved
_isr27:
    cli
    pushl $0
    pushl $27
    jmp isr_common_stub

# 28: Reserved
_isr28:
    cli
    pushl $0
    pushl $28
    jmp isr_common_stub

# 29: Reserved
_isr29:
    cli
    pushl $0
    pushl $29
    jmp isr_common_stub

# 30: Reserved
_isr30:
    cli
    pushl $0
    pushl $30
    jmp isr_common_stub

# 31: Reserved
_isr31:
    cli
    pushl $0
    pushl $31
    jmp isr_common_stub

# externe C funktion fault_handler
.globl _fault_handler
# Prozessor status wird gespeichert, Kernel Segemente werden gesetzt, und C-fault_handler wird aufgerufen, stack frame wird wieder hergestellt
isr_common_stub:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	movw %ax, 0x10
	movw %ds, %ax
	movw %es, %ax
	movw %fs, %ax
	movw %gs, %ax
	movl %eax, %esp
	pushl %eax
	movl $_fault_handler, %eax
	call *%eax
	pop %eax
	pop %gs
	pop %fs
	pop %es
	pop %ds
	popa
	addl $8, %esp
	iret

# Interrupt Request

.global _irq0
.global _irq1
.global _irq2
.global _irq3
.global _irq4
.global _irq5
.global _irq6
.global _irq7
.global _irq8
.global _irq9
.global _irq10
.global _irq11
.global _irq12
.global _irq13
.global _irq14
.global _irq15

.type _irq0, @function
.type _irq1, @function
.type _irq2, @function
.type _irq3, @function
.type _irq4, @function
.type _irq5, @function
.type _irq6, @function
.type _irq7, @function
.type _irq8, @function
.type _irq9, @function
.type _irq10, @function
.type _irq11, @function
.type _irq12, @function
.type _irq13, @function
.type _irq14, @function
.type _irq15, @function

#  32: IRQ0
_irq0:
    cli
    pushl $0
    pushl $32
    jmp irq_common_stub

# 33: IRQ1
_irq1:
    cli
    pushl $0
    pushl $33
    jmp irq_common_stub

# 34: IRQ2
_irq2:
    cli
    pushl $0
    pushl $34
    jmp irq_common_stub

# 35: IRQ3
_irq3:
    cli
    pushl $0
    pushl $35
    jmp irq_common_stub

# 36: IRQ4
_irq4:
    cli
    pushl $0
    pushl $36
    jmp irq_common_stub

# 37: IRQ5
_irq5:
    cli
    pushl $0
    pushl $37
    jmp irq_common_stub

# 38: IRQ6
_irq6:
    cli
    pushl $0
    pushl $38
    jmp irq_common_stub

# 39: IRQ7
_irq7:
    cli
    pushl $0
    pushl $39
    jmp irq_common_stub

# 40: IRQ8
_irq8:
    cli
    pushl $0
    pushl $40
    jmp irq_common_stub

# 41: IRQ9
_irq9:
    cli
    pushl $0
    pushl $41
    jmp irq_common_stub

# 42: IRQ10
_irq10:
    cli
    pushl $0
    pushl $42
    jmp irq_common_stub

# 43: IRQ11
_irq11:
    cli
    pushl $0
    pushl $43
    jmp irq_common_stub

# 44: IRQ12
_irq12:
    cli
    pushl $0
    pushl $44
    jmp irq_common_stub

# 45: IRQ13
_irq13:
    cli
    pushl $0
    pushl $45
    jmp irq_common_stub

# 46: IRQ14
_irq14:
    cli
    pushl $0
    pushl $46
    jmp irq_common_stub

# 47: IRQ15
_irq15:
    cli
    pushl $0
    pushl $47
    jmp irq_common_stub

.globl _irq_handler

irq_common_stub:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	movw %ax, 0x10
	movw %ds, %ax
	movw %es, %ax
	movw %fs, %ax
	movw %gs, %ax
	movl %eax, %esp

	pushl %eax
	movl $_irq_handler, %eax
	call *%eax
	pop %eax

	pop %gs
	pop %fs
	pop %es
	pop %ds
	popa
	addl $8, %esp
	iret
