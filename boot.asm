org 0x7C00 ; start addresse des bootloaders
;	Einrichten des Stacks und Segment Reg
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, ax
	
;	lesen des Kernels von der floppy
	mov [bootdrive], dl		; bootdive liegt default mäßig in DL
	
load_kernel:
	xor ax, ax	;setze ax auf 0 (reset funktion)
	int 0x13
	jc load_kernel ;bei problemen neu laden
	mov bx, 0x8000 ;setzte die start addresse des kernels
	
	; parameter für die reading_function setzten, 8 bit weise für eine bessere übersicht
	mov dl, [bootdrive] ;laufwerk auswählen
	mov al, 0x10	;lies 10 Sektoren
	mov ch, 0x0		;0 Zylinder
	mov cl, 0x2		;2 Sektoren
	mov dh, 0x0		;0 header
	mov ah, 0x2		;"function read"
	int 0x13
	jc load_kernel ; bei problemen neuer versuch
	
	; zeige lodadmsg
	mov si, loadmsg
	call print_string
	
	jmp 0x0000:0x8000 ; Pysikalische Adresse des Kernels

print_string:
	mov ah, 0x0E	;VGA Bios fnct. 0x0E: teletyp
.loop:
	lodsb			;hole ein byte aus si
	test al, al		;null prüfung?
	jz .done		;wenn null gehe aus der schleife
	int 0x10		;wenn nicht gib zeichen aus
	jmp .loop
.done:
	ret
; VAR
	bootdrive db 0
	loadmsg db "Heimdall Message: Der Kernel wird geladen ...", 13, 10, 0
	
	times 510-($-$$) hlt
	db 0x55
	db 0xAA