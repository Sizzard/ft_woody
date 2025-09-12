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

    mov r10, rsp

    sub rsp, 13
    mov rax, 2
    mov rsi, 0
    lea rdi, [rel proc_string]
    syscall ; open("/proc/self/maps", O_RDONLY);

    cmp rax, 0
    jle .error

    mov rdi, rax
    mov rax, 0
    lea rsi, [rsp - 13]
    mov rdx, 12
    syscall ; read(rax, buf, 12);

    cmp rax, 0
    jle .error

    mov rax, 1
    mov rdi, 1
    mov byte [rsp - 1], 0x0a
    lea rsi, [rsp - 13] 
    mov rdx, 13
    syscall ; write(1, buf, 13);    to print the address


    mov byte [rsp - 1], 0x0

; res = rax

    mov rax, 0
    lea rdx, [rsp - 13]
.loop:
    cmp [rdx], byte 0
    je .done

    imul rax, 16
    movzx rcx, byte [rdx]
    cmp [rdx], byte 58
    jg .hex

.dec:
    add rax, rcx
    sub rax, 48
    jmp .inc

.hex:
    add rax, rcx
    sub rax, 87

.inc:
    inc rdx
    jmp .loop

.done:
    add rax, [rel og_entry]    ; rax = address of beginning of program

    ; rdi = unsigned char *text
    mov rsi, [rel size_of_text]; rsi = size_t size
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

    jmp rax

.error:
    xor rdi, rdi
    mov rax, 60
    syscall ; exit(0);

og_entry times 8 db '0'

size_of_text times 8 db 'A'

key times 64 db 0

proc_string:
    db "/proc/self/maps", 0

woody_string:
    db "....WOODY....", 0x0a
    