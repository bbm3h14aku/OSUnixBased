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
	push $0
	push $0
	jmp isr_common_stub

# Debug Exception

_isr1:
	cli
	push $0
	push $1
	jmp isr_common_stub

# Non Maskable Exception

_isr2:
	cli
	push $0
	push $2
	jmp isr_common_stub

# Int 3 Exception
_isr3:
	cli
	push $0
	push $3
	jmp isr_common_stub

# Into Exception
_isr4:
	cli
	push $0
	push $4
	jmp isr_common_stub

# Out of Bounds
_isr5:
	cli
	push $0
	push $5
	jmp isr_common_stub

# Invalid Opcode Exception
_isr6:
	cli
	push $0
	push $6
	jmp isr_common_stub

# Coprozessor Not Available Exception
_isr7:
	cli
	push $0
	push $7
	jmp isr_common_stub

# Double Fault Exception (Mit error code)
_isr8:
	cli
	push $0
	push $8
	jmp isr_common_stub

# Coprocessor Segement Overrun Exception
_isr9:
	cli
	push $0
	push $9
	jmp isr_common_stub

# Bad TSS Exception (Mit Error Code)
_isr10:
	cli
	push $0
	push $10
	jmp isr_common_stub

# Segement not Present Exception
_isr11:
	cli
	push $0
	push $11
	jmp isr_common_stub

# Stack Fault Exception
_isr12:
	cli
	push $0
	push $12
	jmp isr_common_stub

# Genreal Protection Fault Exception
_isr13:
	cli
	push $0
	push $13
	jmp isr_common_stub

# Page Fault Exception
_isr14:
	cli
	push $0
	push $14
	jmp isr_common_stub

# Rserved Exception
_isr15:
	cli
	push $0
	push $15
	jmp isr_common_stub

# Rserved Exception
_isr16:
	cli
	push $0
	push $16
	jmp isr_common_stub

# Rserved Exception
_isr17:
	cli
	push $0
	push $17
	jmp isr_common_stub

# Rserved Exception
_isr18:
	cli
	push $0
	push $18
	jmp isr_common_stub

# Rserved Exception
_isr19:
	cli
	push $0
	push $19
	jmp isr_common_stub

# Rserved Exception
_isr20:
	cli
	push $0
	push $20
	jmp isr_common_stub

# Rserved Exception
_isr21:
	cli
	push $0
	push $21
	jmp isr_common_stub

# Rserved Exception
_isr22:
	cli
	push $0
	push $22
	jmp isr_common_stub

# Rserved Exception
_isr23:
	cli
	push $0
	push $15
	jmp isr_common_stub

# 24: Reserved
_isr24:
    cli
    push $0
    push $24
    jmp isr_common_stub

# 25: Reserved
_isr25:
    cli
    push $0
    push $25
    jmp isr_common_stub

# 26: Reserved
_isr26:
    cli
    push $0
    push $26
    jmp isr_common_stub

# 27: Reserved
_isr27:
    cli
    push $0
    push $27
    jmp isr_common_stub

# 28: Reserved
_isr28:
    cli
    push $0
    push $28
    jmp isr_common_stub

# 29: Reserved
_isr29:
    cli
    push $0
    push $29
    jmp isr_common_stub

# 30: Reserved
_isr30:
    cli
    push $0
    push $30
    jmp isr_common_stub

# 31: Reserved
_isr31:
    cli
    push $0
    push $31
    jmp isr_common_stub

# externe C funktion fault_handler
extern _fault_handler
# Prozessor status wird gespeichert, Kernel Segemente werden gesetzt, und C-fault_handler wird aufgerufen, stack frame wird wieder hergestellt
isr_common_stub:
	pusha
	push %ds
	push %es
	push %fs
	push %gs
	movw %ax, 0x10
	movw %ds, %ax
	movw %es, %ax
	movw %fs, %ax
	movw %gs, %ax
	movl %eax, %esp
	push %eax
	movl %eax, _fault_handler
	call %eax
	pop %eax
	pop %gs
	pop %fs
	pop %es
	pop %ds
	popa
	addl %esp, $8
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

#  32: IRQ0
_irq0:
    cli
    push $0
    push $32
    jmp irq_common_stub

# 33: IRQ1
_irq1:
    cli
    push $0
    push $33
    jmp irq_common_stub

# 34: IRQ2
_irq2:
    cli
    push $0
    push $34
    jmp irq_common_stub

# 35: IRQ3
_irq3:
    cli
    push $0
    push $35
    jmp irq_common_stub

# 36: IRQ4
_irq4:
    cli
    push $0
    push $36
    jmp irq_common_stub

# 37: IRQ5
_irq5:
    cli
    push $0
    push $37
    jmp irq_common_stub

# 38: IRQ6
_irq6:
    cli
    push $0
    push $38
    jmp irq_common_stub

# 39: IRQ7
_irq7:
    cli
    push $0
    push $39
    jmp irq_common_stub

# 40: IRQ8
_irq8:
    cli
    push $0
    push $40
    jmp irq_common_stub

# 41: IRQ9
_irq9:
    cli
    push $0
    push $41
    jmp irq_common_stub

# 42: IRQ10
_irq10:
    cli
    push $0
    push $42
    jmp irq_common_stub

# 43: IRQ11
_irq11:
    cli
    push $0
    push $43
    jmp irq_common_stub

# 44: IRQ12
_irq12:
    cli
    push $0
    push $44
    jmp irq_common_stub

# 45: IRQ13
_irq13:
    cli
    push $0
    push $45
    jmp irq_common_stub

# 46: IRQ14
_irq14:
    cli
    push $0
    push $46
    jmp irq_common_stub

# 47: IRQ15
_irq15:
    cli
    push $0
    push $47
    jmp irq_common_stub

extern _irq_handler

irq_common_stub:
	pusha
	push %ds
	push %es
	push %fs
	push %gs

	movw %ax, 0x10
	movw %ds, %ax
	movw %es, %ax
	movw %fs, %ax
	movw %gs, %ax
	movl %eax, %esp

	push %eax
	movl %eax, _irq_handler
	call %eax
	pop %eax

	pop %gs
	pop %fs
	pop %es
	pop %ds
	popa
	addl %esp, $8
	iret
