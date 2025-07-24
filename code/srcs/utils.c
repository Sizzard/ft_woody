#include "../woody.h"

void print_ehdr(const Elf64_Ehdr *eHdr) {
    puts("eHdr ---------------");
    printf("e_type          = 0x%08X, %d\n", eHdr->e_type, eHdr->e_type);
    printf("e_machine       = 0x%08X, %d\n", eHdr->e_machine, eHdr->e_machine);
    printf("e_version       = 0x%08X, %d\n", eHdr->e_version, eHdr->e_version);
    printf("e_entry         = 0x%08lX, %lu\n", eHdr->e_entry, eHdr->e_entry);
    printf("e_phoff         = 0x%08lX, %lu\n", eHdr->e_phoff, eHdr->e_phoff);
    printf("e_shoff         = 0x%08lX, %lu\n", eHdr->e_shoff, eHdr->e_shoff);
    printf("e_flags         = 0x%08X, %d\n", eHdr->e_flags, eHdr->e_flags);
    printf("e_ehsize        = 0x%08X, %d\n", eHdr->e_ehsize, eHdr->e_ehsize);
    printf("e_phentsize     = 0x%08X, %d\n", eHdr->e_phentsize, eHdr->e_phentsize);
    printf("e_phnum         = 0x%08X, %d\n", eHdr->e_phnum, eHdr->e_phnum);
    printf("e_shentsize     = 0x%08X, %d\n", eHdr->e_shentsize, eHdr->e_shentsize);
    printf("e_shnum         = 0x%08X, %d\n", eHdr->e_shnum, eHdr->e_shnum);
    printf("e_shstrndx      = 0x%08X, %d\n", eHdr->e_shstrndx, eHdr->e_shstrndx);
}

void print_phdr(const Elf64_Phdr *pHdr) {
    puts("pHdr ---------------");
    printf("p_type      =   0x%08x -- %d\n", pHdr->p_type, pHdr->p_type);
    printf("p_flags     =   0x%08x -- %d\n", pHdr->p_flags, pHdr->p_flags);
    printf("p_offset    =   0x%08lx -- %ld\n", pHdr->p_offset, pHdr->p_offset);
    printf("p_vaddr     =   0x%08lx -- %ld\n", pHdr->p_vaddr, pHdr->p_vaddr);
    printf("p_paddr     =   0x%08lx -- %ld\n", pHdr->p_paddr, pHdr->p_paddr);
    printf("p_filesz    =   0x%08lx -- %ld\n", pHdr->p_filesz, pHdr->p_filesz);
    printf("p_memsz     =   0x%08lx -- %ld\n", pHdr->p_memsz, pHdr->p_memsz);
    printf("p_align     =   0x%08lx -- %ld\n", pHdr->p_align, pHdr->p_align);
}

void print_all_phdr(t_file *file, const Elf64_Ehdr *eHdr) {

    for(uint16_t i = 0; i < eHdr->e_phnum; i++) {
        const Elf64_Phdr *pHdr = (Elf64_Phdr *)(file->ptr + eHdr->e_phoff + i * eHdr->e_phentsize);
        print_phdr(pHdr);
    }

}

Elf64_Phdr *find_pt_note_phdr(t_file *file, const Elf64_Ehdr *eHdr) {
    for(uint16_t i = 0; i < eHdr->e_phnum; i++) {
        Elf64_Phdr *pHdr = (Elf64_Phdr *)(file->ptr + eHdr->e_phoff + i * eHdr->e_phentsize);
        if (pHdr->p_type == PT_NOTE) {
            return pHdr;
        }
    }
    return NULL;
}

// bool replace_in_file(int fd, size_t pos, size_t to_add, char *buf) {
//     char buffer[16384] = {0};
// 	int red;

//     lseek(fd, pos, SEEK_SET);
//     red = read(fd, buffer, sizeof(buffer));
//     lseek(fd, pos, SEEK_SET);
//     write(fd, buf, to_add);
//     lseek(fd, pos + to_add, SEEK_SET);
//     write(fd, buffer, red);
//     return false;
// }

t_file *open_file(char *file_name) {
    t_file      *file = malloc(sizeof(t_file));

    if (file == NULL) {
        fprintf(stderr, "woody: Can't allocate memory\n");
        return NULL;
    }

    file->path = file_name;

    file->fd = open(file_name, O_RDWR);
    if (file->fd == -1) {
        fprintf(stderr, "woody: Can't open file\n");
        return NULL;
    }

    file->size = lseek(file->fd, 0, SEEK_END);
    if (file->size == (off_t) -1) {
        fprintf(stderr, "woody: Can't seek file\n");
        return NULL;
    }

    file->ptr = mmap(0, file->size, PROT_READ | PROT_WRITE, MAP_SHARED, file->fd, 0);
    if (file->ptr == (void *) -1) {
        fprintf(stderr, "woody: Can't mmap file\n");
        return NULL;
    }

    return file;
}