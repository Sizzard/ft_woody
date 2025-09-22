global woody

section .text

woody:
    mov rdi, 1
    lea rsi, [rel woody_string]
    mov rdx, 14
    mov rax, 1
    syscall ; write(1, "....WOODY....", 14);

    cmp rax, 0
    jle .error

    xor rcx, rcx
    mov ecx , dword [rel og_entry]         
    add rax, rcx                    ; rax = address of beginning of program
    mov r10, rax
    mov rsi, qword [rel size_of_text]   ; rsi = len

    mov rdi, r10
    and rdi, -0x1000

    mov rax, r10
    add rax, rsi
    add rax, 0xfff
    and rax, -0x1000

    sub rax, rdi
    mov rsi, rax

    mov rdx, 7                   ; PROT_READ|PROT_WRITE|PROT_EXEC
    mov rax, 10                  ; syscall mprotect
    syscall                  ; mprotect(og_entry, size_of_text, PROT_READ, PROT_WRITE, PROT_EXEC)
    cmp rax, 0
    jl .error
    mov rax, r10

    mov rsi, [rel size_of_text]     ; rsi = size_t size
    lea r10, [rel key]              ; unsigned char *K

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

    xor rdi, rdi
    xor rsi, rsi
    xor rdx, rdx
    jmp rax

.error:
    xor rdi, rdi
    mov rax, 60
    syscall ; exit(0);

og_entry times 8 db '0'

size_of_text times 8 db 'A'

key times 64 db 0
woody_string:
    db "....WOODY....", 0x0a
    