#ifndef KEYBOARD_ENEN_H
#define KEYBOARD_ENEN_H

#define NULL 0
#define ESC       27
#define BACKSPACE '\b'
#define TAB       '\t'
#define ENTER     '\n'
#define RETURN    '\r'
#define NEWLINE   ENTER

// Non-ASCII special scancodes // Esc in scancode is 1
#define    KESC         1
#define    F1          0x80
#define    F2         (F1 + 1)
#define    F3         (F2 + 1)
#define    F4         (F3 + 1)
#define    F5         (F4 + 1)
#define    F6         (F5 + 1)
#define    F7         (F6 + 1)
#define    F8         (F7 + 1)
#define    F9         (F8 + 1)
#define    F10        (F9 + 1)
#define    F11        (F10 + 1)
#define    F12        (F11 + 1)

// Cursor Keys
#define    INS         0x90
#define    DEL        (INS + 1)
#define    HOME       (DEL + 1)
#define    END        (HOME + 1)
#define    PGUP       (END + 1)
#define    PGDN       (PGUP + 1)
#define    LEFT       (PGDN + 1)
#define    UP         (LEFT + 1)
#define    DOWN       (UP + 1)
#define    RIGHT      (DOWN + 1)

// "Meta" keys
#define    META_ALT     0x0200                                // Alt is pressed
#define    META_CTRL    0x0400                                // Ctrl is pressed
#define    META_SHIFT   0x0800                                // Shift is pressed
#define    META_ANY    (KMETA_ALT | KMETA_CTRL | KMETA_SHIFT)
#define    META_CAPS    0x1000                                // CapsLock is on
#define    META_NUM     0x2000                                // NumLock is on
#define    META_SCRL    0x4000                                // ScrollLock is on

// Other keys
#define    PRNT    ( KRT + 1 )
#define    PAUSE   ( KPRNT + 1 )
#define    LWIN    ( KPAUSE + 1 )
#define    RWIN    ( KLWIN + 1 )
#define    MENU    ( KRWIN + 1 )

#define    RLEFT_CTRL        0x1D
#define    RRIGHT_CTRL       0x1D

#define    RLEFT_ALT         0x38
#define    RRIGHT_ALT        0x38

#define    RLEFT_SHIFT       0x2A
#define    RRIGHT_SHIFT      0x36

#define    RCAPS_LOCK        0x3A
#define    RSCROLL_LOCK      0x46
#define    RNUM_LOCK         0x45
#define    RDEL              0x53

#define MAXKEYBUFFER 64       // max keyboard buffer

// Keymaps: US International

// Non-Shifted scan codes to ASCII:
static unsigned char asciiNonShift[] = {
NULL, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', BACKSPACE,
TAB, 'q', 'w',   'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',   '[', ']', ENTER, 0,
'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' ', 0,
F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, 0, 0,
HOME, UP, PGUP,'-', LEFT, '5', RIGHT, '+', END, DOWN, PGDN, INS, DEL, 0, 0, 0, F11, F12 };

// Shifted scan codes to ASCII:
static unsigned char asciiShift[] = {
NULL, ESC, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', BACKSPACE,
TAB, 'Q', 'W',   'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',   '{', '}', ENTER, 0,
'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', 0, '|',
'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, 0, 0, ' ', 0,
F1,   F2, F3, F4, F5, F6, F7, F8, F9, F10, 0, 0,
HOME, UP, PGUP, '-', LEFT, '5',   RIGHT, '+', END, DOWN, PGDN, INS, DEL, 0, 0, 0, F11, F12 };

#endif
