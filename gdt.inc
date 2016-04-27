; GDT Table
; Es werden 3 Deskriptoren angelegt dise werden nur im Protected Mode benötigt der RealMode hat eine konstante
; größe von 64 KByte, die Maximale Anzahl an Diskriptoren liegt bei 8192 Deskriptoren
NULL_Desc:
	dd	0
	dd	0
	
CODE_Desc:
	dw	0xFFFF		; segment länge bits 0 - 15 
	dw	0			; segment Base byte 0,1
	db	0			; segment Base byte 2
	db	10011010b	; access rights
	db	11001111b	; bit 7 -4 FLAG Bit, default Operation Size
	db	0			; segemnts Base byte 3
	
DATA_Desc:
	dw	0xFFFF
	dw	0
	dw	0
	db	10011010b
	db	11001111b
	db	0
	
gdtr:
Limit 	dw 24			; länge von GDT
Base	dd NULL_Desc	; größe von GDT (lineare Addresse: RM Offset + Seg<<4)