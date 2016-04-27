;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; DOORS VERSION 0.04 version from october 30, 2015 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

org 0x8000
	[BITS 16]
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;		Echte Modus / REAL MODE						;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

RealMode:
	mov si, eintieg
	call print_string
	
	xor ax, ax
	mov es, ax
	mov ds, ax
	mov ss, ax
	mov sp, ax
	
	mov si, welcome
	call print_string
	
	add sp, -0x40
	
loop_start:
	mov si, prompt		;zeige Prompt
	call print_string
	
	mov di, sp			;bekomme input
	call get_string
	jcxz loop_start		;leere Zeile = ignorieren
	
	mov si, sp
	mov di, cmd_hi		;hi command
	je .hello
	
	mov si, sp
	mov di, cmd_help	;help command
	je .help
	
	mov si, sp
	mov di, cmd_questionmark	;zweite help command
	je .help
	
	mov si, sp		;reboot command
	mov di, cmd_reboot
	je .reboot
	
	mov si, sp	;pm command
	mov di, cmd_pm
	je .pm
	
	mov si, badcommand	; unbekanntes commando
	call print_string
	jmp loop_start

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Funktionen				;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.calc:
	mov si, msg_calc
	call print_string
	mov di, sp
	call get_string
	
.hello:
	mov si, msg_hello
	call print_string
	jmp loop_start
	
.help:
	mov si, msg_help
	call print_string
	jmp loop_start

.reboot:
	mov si, msg_reboot
	call print_string
	xor ax, ax
	int 0x16
	jmp 0xffff:0x0000
	
.pm:
	call clrscr
	mov si, msg_pm
	call print_string
	call Waitingloop
	
	cli		;interupts werden gesäubert
	lgdt [gdtr] ;lade GDT via GDTR (liegt in der gtd.inc)
	
	in al, 0x92
	cmp al, 0xff
	je .no_fast_A20
	
	or al, 2
	and al, ~1
	out 0x92, al
	jmp .A20_done
	
.no_fast_A20:
	call empty_8042
	
	mov al, 0xD1
	out 0x64, al
	call empty_8042
	
	mov al, 0xDF
	out 0x60, al
	call empty_8042
	
.A20_done:
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	
	jmp 0x8:ProtectedMode 
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Aufrufe 							 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

empty_8042:
	call Waitingloop
	in al, 0x64
	cmp al, 0xff
	je .done
	
	test al, 1
	jz .no_output
	call Waitingloop
	in al, 0x60
	jmp empty_8042
	
.no_output:
	test al, 2
	jnz empty_8042
.done:
ret

print_string:
	xor ah, 0x0E
.loop_start:
	lodsb
	test al, al
	jz .done
	int 0x10
	jmp .loop_start
.done:
	ret
	
get_string:
	xor cx, cx
.loop_start:
	xor ax, ax
	int 0x16
	cmp al, 8
	je .backspace
	cmp al, 13
	je .done
	cmp cl, 63
	je .loop_start
	mov ah, 0x0E
	int 0x10
	stosb
	inc cx
	jmp .loop_start
	
.backspace:
	jcxz .loop_start
	dec di
	mov byte [di], 0
	dec cx
	mov ah, 0x0E
	int 0x10
	mov al, ' '
	int 0x10
	mov al, 8
	int 0x10
	jmp .loop_start
	
.done:
	mov byte [di], 0
	mov ax, 0x0E0D
	int 0x10
	mov al, 0x0A
	int 0x10
	ret
	
strcmp:
.loop_start:
	mov al, [si]
	cmp al, [di]
	jne .done
	
	test al, al
	jz .done
	
	inc di
	inc si
	jmp .loop_start
	
.done:
	ret
	
clrscr:
	mov ax, 0x0600
	xor cx, cx
	mov dx, 0x174F
	mov bh, 0x07
	int 0x10
	ret
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 	Protected Mod			   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[Bits 32]

ProtectedMode:
	mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	xor eax, eax
	mov fs, ax
	mov gs, ax
	mov esp, 0x200000
	
	call clrscr_32
	mov ah, 0x01
.endlessloop:
	call xWaitingloop
	inc ah
	and ah, 0x0f
	mov esi, msg_pm2
	call PutStr_32
	cmp dword [xPutStr_Ptr], 25 * 80 *2 + 0xB8000
	jb .endlessloop
	cmp dword [xPutStr_Ptr], 0xB8000
	jmp .endlessloop
	
xWaitingloop:
	mov ebx, 0x9FFFF
.loop_start:
	dec ebx
	jnz .loop_start
	ret
	
PutStr_64:
	mov edi, [xPutStr_Ptr]
.nextchar:
	lodsb
	test al, al
	jz .end
	stosw
	jmp .nextchar
  .end:
	mov [xPutStr_Ptr], edi
	ret
	
clrscr_32:
	mov edi, 0xB8000
	mov [xPutStr_Ptr], edi
	mov ecx, 40 * 25
	mov eax, 0x07200720
	rep stosd
	ret

xPutStr_Ptr dd 0xB8000

[Bits 64]

amd64:
	mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	xor rax, rax
	mov fs, ax
	mov gs, ax
	mov rsp, 0x200000
	
	call clrscr_64
	mov ah, 0x01
.xendlessloop:
	call Waitingloop
	inc ah
	and ah, 0x0f
	mov rsi, msg_pm2
	call PutStr_64
	cmp dword [PutStr_Ptr], 25 * 80 *2 + 0xB8000
	jb .xendlessloop
	cmp dword [PutStr_Ptr], 0xB8000
	jmp .xendlessloop
	
Waitingloop:
	mov rbx, 0x9FFFF
.xloop_start:
	dec rbx
	jnz .xloop_start
	ret
	
PutStr_64:
	mov rdi, [xPutStr_Ptr]
.nextchar:
	lodsb
	test al, al
	jz .end
	stosw
	jmp .nextchar
  .end:
	mov [PutStr_Ptr], rdi
	ret
	
clrscr_64:
	mov rdi, 0xB8000
	mov [PutStr_Ptr], rdi
	mov rcx, 40 * 25
	mov rax, 0x07200720
	rep stosd
	ret

PutStr_Ptr dd 0xB8000
	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;		Strings					  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
eintieg db 'ok',13,10,0
welcome db 'DOORS OS VERSION 0.04', 13, 10, 0
msg_hello db 'Hello', 13, 10, 0
badcommand db 'Unbekanntes Kommando', 13, 10, 0
prompt db '~>', 0
cmd_hi db 'hi', 0
cmd_help db 'help', 0
cmd_questionmark db '?', 0
cmd_reboot db 'reboot', 0
cmd_pm db 'pm', 0
cmd_calc db 'calc', 0
msg_help db 'Befehle: hi, help, ?, reboot, pm', 13, 10, 0
msg_reboot db 'Neustart wird jetzt durchgefuehrt', 13, 10, 0
msg_pm db 'Wechsel in den Protected Mode', 13, 10, 0
msg_pm2 db 'OS laueft bereits im Protected Mode', 13, 10, 0
msg_calc db 'Bitte geben Sie den X Wert ein', 13, 10, 0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;	includes					  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%include "gdt.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;	set Bits to hlt				   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

times 1024-($-$$) hlt