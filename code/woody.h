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

typedef struct s_file {
    int         fd;
    off_t       size;
    char        *path;
    uint8_t     *ptr;
}   t_file;

t_file      *open_file(char *file_name);
void        print_ehdr(const Elf64_Ehdr *eHdr);