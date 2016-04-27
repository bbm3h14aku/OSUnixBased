mov ax, 0x07C0  ; set up segments
  mov ds, ax
  mov es, ax

  mov si, welcome
  call print_string

loop:
  mov si, prompt
  call print_string

  mov di, buffer
  call get_string

  mov si, buffer
  cmp byte [si], 0  ; blank line?
  je loop           ; yes, ignore it

  mov di, cmd_hi    ; "hi" command
  call strcmp
  jz .helloworld

  mov si, buffer
  mov di, cmd_help  ; "help" command
  call strcmp
  jz .help

  mov si, buffer
  mov di, cmd_questionmark  ; "?" command
  call strcmp
  jz .help
 
  mov si, buffer
  mov di, cmd_exit  ; "exit" command
  call strcmp
  jz .exit

  mov si,badcommand
  call print_string
  jmp loop 

.helloworld:
  mov si, msg_helloworld
  call print_string

  jmp loop

.help:
  mov si, msg_help
  call print_string

  jmp loop

.exit:
  mov si, msg_exit
  call print_string
  jmp 0xffff:0x0000  ; Reboot

welcome db 'HenkesSoft 0.01 (version from Mar 14, 2009)', 13, 10, 0
msg_helloworld db 'Hello World!', 13, 10, 0
badcommand db 'Command unknown.', 13, 10, 0
prompt db '>', 0
cmd_hi db 'hi', 0
cmd_help db 'help', 0
cmd_questionmark db '?', 0
cmd_exit db 'exit', 0
msg_help db 'Commands: hi, help, ?, exit', 13, 10, 0
msg_exit db 'Reboot starts now.', 13, 10, 0

buffer times 32 db 0

; ================
; calls start here
; ================

print_string:
  lodsb        ; grab a byte from SI

  or al, al    ; logical or AL by itself
  jz .done     ; if the result is zero, get out

  mov ah, 0x0E
  int 0x10       ; otherwise, print out the character!

  jmp print_string

.done:
  ret

get_string:
  xor cl, cl

.loop:
  xor ah, ah    ; mov ah, 0
  int 0x16      ; wait for keypress

  cmp al, 8     ; backspace pressed?
  je .backspace ; yes, handle it

  cmp al, 13    ; enter pressed?
  je .done      ; yes, we're done

  cmp cl, 31    ; 31 chars inputted?
  je .loop      ; yes, only let in backspace and enter

  mov ah, 0x0E
  int 0x10      ; print out character

  stosb  ; put character in buffer
  inc cl
  jmp .loop

.backspace:
  or cl, cl     ; zero? (start of the string)
  jz .loop      ; if yes, ignore the key

  dec di
  mov byte [di], 0  ; delete character
  dec cl        ; decrement counter as well

  mov ax, 0x0E08
  int 0x10      ; backspace on the screen

  mov al, ' '
  int 0x10      ; blank character out

  mov al, 8
  int 0x10      ; backspace again

  jmp .loop     ; go to the main loop

.done:
  mov al, 0     ; null terminator
  stosb

  mov ax, 0x0E0D
  int 0x10
  mov al, 0x0A
  int 0x10      ; newline

  ret

strcmp:
.loop:
  mov al, [si]   ; fetch a byte from SI
  cmp al, [di]   ; are SI and DI equal?
  jne .done      ; if no, we're done.

  or al, al      ; zero?
  jz .done       ; if yes, we're done.

  inc di         ; increment DI
  inc si         ; increment SI
  jmp .loop      ; goto .loop

.done:    
  ret

  times 510-($-$$) hlt  ; as alternative to db 0
  db 0x55        ; boot signature check (byte 511 in sector 1)
  db 0xAA        ; boot signature check (byte 512 in sector 1)
