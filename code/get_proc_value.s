global get_proc_value

section .text

;rsp - 13 = buf

get_proc_value:
    mov r10, rsp

    sub rsp, 13
    mov rax, 2
    mov rsi, 0
    lea rdi, [rel proc_string]
    syscall ; open("/proc/self/maps", O_RDONLY);

    mov rdi, rax
    mov rax, 0
    lea rsi, [rsp - 13]
    mov rdx, 12
    syscall ; read(rax, buf, 12);


    mov rax, 1
    mov rdi, 1
    mov byte [rsp - 1], 0x0a
    lea rsi, [rsp - 13] 
    mov rdx, 13
    syscall ; write(1, buf, 13);


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
    mov rsp, r10
    ret

proc_string:
    db "/proc/self/maps", 0