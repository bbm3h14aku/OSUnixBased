;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;	Global Description Table (GDT)	;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

NULL_Desc:
	dd	0
	dd	0
	
CODE_Desc:
	dw	0xFFFF	;länge des Segments 0 - 15 bits
	dw 	0		;basis Segment byte 0,1
	db	0		;basis Segment byte 2
	db	10011010b	;acces rights
	db	11001111b	;bit 7 - 4 4 Flag bits genauigkeit, default Operation size bit
	
	db	0
	
DATA_Desc:
	dw	0xFFFF
	dw	0
	db	0
	db	10010010b
	db	11001111b
	
	db	0
	
gdtr:
Limit	dw	24
Base	dd NULL_Desc