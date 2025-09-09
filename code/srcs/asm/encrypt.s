global encrypt

section .text

encrypt:
    push rbp
    mov rbp, rsp
    
    sub rsp, 256
    xor rdi, rdi
.create_stream:
    cmp rdi, 256
    jg .create_stream_done
    mov [rbp - 256 + rdi], rdi
    inc rdi
    jmp .create_stream

.create_stream_done:

    mov rdi, 1
    lea rsi, [rbp - 256]
    mov rdx, 256
    mov rax, 1
    syscall ; write(1, "0123...", 256);

    xor rdi, rdi
.init_stream:
    cmp rdi, 256
    jae .init_stream_done

    movzx rax, byte [rbp - 256 + rdi]

    add rsi, rax

    movzx rax, byte [rel key + rdi]

    add rsi, rax

    and rsi, 0FFh

    mov al, [rbp - 256 + rdi]

    mov bl, [rbp - 256 + rsi]

    mov [rbp - 256 + rdi], bl

    mov [rbp - 256 + rsi], al

    inc rdi
    jmp .init_stream

.init_stream_done:


    mov rsp, rbp
    pop rbp
    ret

key:
    db "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"