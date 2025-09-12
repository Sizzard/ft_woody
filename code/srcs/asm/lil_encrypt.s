global lil_encrypt

section .text

lil_encrypt:
    ; rdi = unsigned char *text
    ; rsi = size_t size
    lea r10, [rel key]              ; unsigned char *K

    mov rax, rdi    ; rax = address

    xor rdi, rdi
    xor r8, r8  ; i
    xor r9, r9  ; j
.crypt_loop:
    cmp r8, rsi
    jae .crypt_done
    mov r9, r8
    and r9, 63
    mov cl, [rax + r8]
    xor cl, [r10 + r9]
    mov [rax + r8], cl
    inc r8
    jmp .crypt_loop
.crypt_done:

    ret


key times 64 db '0'