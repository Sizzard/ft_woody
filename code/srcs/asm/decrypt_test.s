global decrypt_test

section .text

;rsp - 13 = buf

decrypt_test:
    mov rax, 10
    lea rdi, [rel .label]
    mov rsi, 20
    mov rdx, 7
    syscall
    cmp rax, 0
    jl .exit
