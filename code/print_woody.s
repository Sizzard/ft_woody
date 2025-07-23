global print_woody

section .text

;0x2e0x2e0x2e0x2e
;0x570x4f0x4f0x44
;0x590x2e0x2e0x2e
;0x2e0xa0

print_woody:
  mov rax, 1
  mov rdi, 1
  mov rdx, 4
  push 0x2e2e2e2e
  mov rsi, rsp
  syscall
  mov rax, 1
  push 0x444f4f57
  mov rsi, rsp
  syscall
  mov rax, 1
  push 0x2e2e2e59
  mov rsi, rsp
  syscall
  mov rax, 1
  mov rdx, 2
  push 0x0a2e
  mov rsi, rsp
  syscall
  mov rax, 60
  mov rdi, 42
  syscall