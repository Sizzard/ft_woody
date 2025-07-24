global print_woody

section .text

print_woody:
  mov rbx, rsp
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
  xor rax, rax
  xor rdx, rdx
  mov rsp, rbx