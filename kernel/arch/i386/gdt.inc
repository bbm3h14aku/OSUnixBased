;; Global Descriptor Table (GDT)

NULL_Desc:
	dd	0
	dd	0
	
CODE_Desc:
	dw	0xFFFF
	dw	0
	db	0
	db	10011010b
	db	11001111b
	
	db 0
	
DATA_Desc:
	dw	0xFFFF
	dw	0
	db	0
	db 	10010010b
	db	11001111b
	
	db	0
	
gdtr:
	Limit	dw	24
	Base	dd	NULL_Desc