; asmsyntax=nasm
section .text

global hsort_move

; void move(void *x, void *y, void *buf, size_t size);

hsort_move:
mov   r8,   rdi
mov   r9,   rsi
mov   r10,  rdx
mov   r11,  rcx

mov   rdi,  r10
mov   rsi,  r8
rep   movsb

mov   rcx,  r11
mov   rdi,  r8
mov   rsi,  r9
rep   movsb

mov   rcx,  r11
mov   rdi,  r9
mov   rsi,  r10
rep   movsb

ret
