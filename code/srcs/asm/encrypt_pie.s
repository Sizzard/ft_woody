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
    mov rsp, r10
    xor rdi, rdi
    xor rdx, rdx
    add rax, 0xaaaaaaaa ; rax = address of beginning of program

    push rax
    push rbp
    mov rbp, rsp
    
    sub rsp, 256

    ; rdi = unsigned char *text
    ; rsi = size_t size
    lea r10, [rel key]              ; unsigned char *K

    xor r8, r8
.create_stream:
    cmp r8, 256
    jae .create_stream_done
    mov [rbp - 256 + r8], r8b
    inc r8
    jmp .create_stream

.create_stream_done:

; print_key:
;     mov rdi, 1
;     lea rsi, [rbp - 256]
;     mov rdx, 256
;     mov rax, 1
;     syscall ; write(1, "0123...", 256);

; print_text:
;     mov rax, 1
;     mov rdi, 1
;     lea rsi, [r8]
;     mov rdx, 256
;     syscall ;

    xor r8, r8  ; i = 0
    xor r9, r9  ; j = 0
.init_stream:
    cmp r8, 256
    jae .init_stream_done

    movzx rax, byte [rbp - 256 + r8]
    add r9, rax

    movzx rax, byte [r10 + r8]
    add r9, rax

    and r9, 0FFh

    mov al, [rbp - 256 + r8]       ;swap

    mov bl, [rbp - 256 + r9]

    mov [rbp - 256 + r8], bl

    mov [rbp - 256 + r9], al       ; end swap, R10, R11,

    inc r8
    jmp .init_stream

.init_stream_done:

PRGA:
    xor r10, r10    ; idx
    xor r8, r8    ; i
    xor r9, r9    ; j

PRGA_loop:

    cmp r10, 256
    jae PRGA_done

    inc r8
    
    and r8, 0FFh

    movzx rax, byte [rbp - 256 + r8]
    add r9, rax

    and r9, 0FFh

    mov al, [rbp - 256 + r8]       ;swap

    mov bl, [rbp - 256 + r9]

    mov [rbp - 256 + r8], bl

    mov [rbp - 256 + r9], al       ; end swap

    inc r10         ;idx++

    jmp PRGA_loop

PRGA_done:

    xor r8, r8
    pop rax
crypt_loop:
    cmp r8, rsi
    jae crypt_done
    mov al, [rbp - 256 + r8]
    xor al, [rdi + r8]
    mov [rdi + r8], al
    inc r8
    jmp crypt_loop
crypt_done:

    mov rsp, rbp
    pop rbp
    jmp rax


key times 256 db '0'

.error:
    xor rdi, rdi
    mov rax, 60
    syscall ; exit(0);

key times 256 db '0'

proc_string:
    db "/proc/self/maps", 0

woody_string:
    db "....WOODY....", 0x0a
    