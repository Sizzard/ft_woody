#include "../woody.h"

void print_ehdr(const Elf64_Ehdr *eHdr) {
    // printf(" %d\n", eHdr->e_ident[EI_NIDENT]);
    printf("e_type          = 0x%X, %d\n", eHdr->e_type, eHdr->e_type);
    printf("e_machine       = 0x%X, %d\n", eHdr->e_machine, eHdr->e_machine);
    printf("e_version       = 0x%X, %d\n", eHdr->e_version, eHdr->e_version);
    printf("e_entry         = 0x%lX, %lu\n", eHdr->e_entry, eHdr->e_entry);
    printf("e_phoff         = 0x%lX, %lu\n", eHdr->e_phoff, eHdr->e_phoff);
    printf("e_shoff         = 0x%lX, %lu\n", eHdr->e_shoff, eHdr->e_shoff);
    printf("e_flags         = 0x%X, %d\n", eHdr->e_flags, eHdr->e_flags);
    printf("e_ehsize        = 0x%X, %d\n", eHdr->e_ehsize, eHdr->e_ehsize);
    printf("e_phentsize     = 0x%X, %d\n", eHdr->e_phentsize, eHdr->e_phentsize);
    printf("e_phnum         = 0x%X, %d\n", eHdr->e_phnum, eHdr->e_phnum);
    printf("e_shentsize     = 0x%X, %d\n", eHdr->e_shentsize, eHdr->e_shentsize);
    printf("e_shnum         = 0x%X, %d\n", eHdr->e_shnum, eHdr->e_shnum);
    printf("e_shstrndx      = 0x%X, %d\n", eHdr->e_shstrndx, eHdr->e_shstrndx);
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

    file->fd = open(file_name, O_RDONLY);
    if (file->fd == -1) {
        fprintf(stderr, "woody: Can't open file\n");
        return NULL;
    }

    file->size = lseek(file->fd, 0, SEEK_END);
    if (file->size == (off_t) -1) {
        fprintf(stderr, "woody: Can't seek file\n");
        return NULL;
    }

    file->ptr = mmap(0, file->size, PROT_READ | PROT_WRITE, MAP_PRIVATE, file->fd, 0);
    if (file->ptr == (void *) -1) {
        fprintf(stderr, "woody: Can't mmap file\n");
        return NULL;
    }

    return file;
}