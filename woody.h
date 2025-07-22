#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>

uint8_t     *open_file(char *file_name);
void        print_ehdr(const Elf64_Ehdr *eHdr);