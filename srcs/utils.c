#include "../woody.h"

void print_ehdr(const Elf64_Ehdr *eHdr) {
    // printf(" %d\n", eHdr->e_ident[EI_NIDENT]);
    printf("e_type = %d\n", eHdr->e_type);
    printf("e_machine = %d\n", eHdr->e_machine);
    printf("e_version = %d\n", eHdr->e_version);
    printf("e_entry = %lu\n", eHdr->e_entry);
    printf("e_phoff = %lu\n", eHdr->e_phoff);
    printf("e_shoff = %lu\n", eHdr->e_shoff);
    printf("e_flags = %d\n", eHdr->e_flags);
    printf("e_ehsize = %d\n", eHdr->e_ehsize);
    printf("e_phentsize = %d\n", eHdr->e_phentsize);
    printf("e_phnum = %d\n", eHdr->e_phnum);
    printf("e_shentsize = %d\n", eHdr->e_shentsize);
    printf("e_shnum = %d\n", eHdr->e_shnum);
    printf("e_shstrndx = %d\n", eHdr->e_shstrndx);
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

uint8_t *open_file(char *file_name) {
    int     fd;
    off_t   file_size;
    uint8_t *file;

    fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "woody: Can't open file\n");
        return NULL;
    }

    file_size = lseek(fd, 0, SEEK_END);
    if (file_size == (off_t) -1) {
        fprintf(stderr, "woody: Can't seek file\n");
        return NULL;
    }

    file = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (file == (void *) -1) {
        fprintf(stderr, "woody: Can't mmap file\n");
        return NULL;
    }
    return file;
}