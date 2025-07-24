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

#define PAYLOAD_SIZE 100

t_file              *open_file(char *file_name);
void                print_ehdr(const Elf64_Ehdr *eHdr);
void                print_all_phdr(t_file *file, const Elf64_Ehdr *eHdr) ;
void                print_phdr(const Elf64_Phdr *pHdr);
Elf64_Phdr          *find_pt_note_phdr(t_file *file, const Elf64_Ehdr *eHdr);
void                hijack_phdr(t_file *file, Elf64_Ehdr *eHdr, Elf64_Phdr *pHdr);
bool                append_payload(t_file *file, uint64_t og_entry);