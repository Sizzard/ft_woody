global print_woody

section .text

print_woody:
    mov rdi, 1
    lea rsi, [rel woody_string]
    mov rdx, 14
    mov rax, 1
    syscall
    xor rdi, rdi
    xor rdx, rdx
    mov rax, 0x0000000000000000
    jmp rax

woody_string:
    db "....WOODY....", 0x0a
    