;write(1, "Hello World!\n", 13);

global ft_write

section .text

secret:
    db 'Hello', 0xA

ft_write:
  
  mov rdi, 1
  mov rsi, secret
  mov rdx, 13
  mov rax, 1        ; write(
  syscall           ; );
  ;jmp