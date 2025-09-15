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

void print_shdr(const Elf64_Shdr *shdr) {
    printf("sh_name         = 0x%08x -- %d\n", shdr->sh_name, shdr->sh_name);
    printf("sh_type         = 0x%08x -- %d\n", shdr->sh_type, shdr->sh_type);
    printf("sh_flags        = 0x%08lx -- %ld\n", shdr->sh_flags, shdr->sh_flags);
    printf("sh_addr         = 0x%08lx -- %ld\n", shdr->sh_addr, shdr->sh_addr);
    printf("sh_offset       = 0x%08lx -- %ld\n", shdr->sh_offset, shdr->sh_offset);
    printf("sh_size         = 0x%08lx -- %ld\n", shdr->sh_size, shdr->sh_size);
    printf("sh_link         = 0x%08x -- %d\n", shdr->sh_link, shdr->sh_link);
    printf("sh_info         = 0x%08x -- %d\n", shdr->sh_info, shdr->sh_info);
    printf("sh_addralign    = 0x%08lx -- %ld\n", shdr->sh_addralign, shdr->sh_addralign);
    printf("sh_entsize      = 0x%08lx -- %ld\n", shdr->sh_entsize, shdr->sh_entsize);
}

void print_all_phdr(t_file *file, const Elf64_Ehdr *eHdr) {

    for(uint16_t i = 0; i < eHdr->e_phnum; i++) {
        const Elf64_Phdr *pHdr = (Elf64_Phdr *)(file->ptr + eHdr->e_phoff + i * eHdr->e_phentsize);
        print_phdr(pHdr);
    }

}

int	ft_strncmp(const uint8_t *s1, const uint8_t *s2, size_t n)
{
	size_t	i;
	int		res;

	if (!s1 || !s2)
		return (1);
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		i++;
	res = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (res);
}

size_t ft_strlen(const char *str) {
    int i = 0;
    while (str[i]) {
        i++;
    }
    return i;
}

Elf64_Shdr *find_texttab(t_file *file, const Elf64_Ehdr *eHdr) {
    const Elf64_Shdr *shStrTab = (Elf64_Shdr *)&file->ptr[eHdr->e_shoff + (sizeof(Elf64_Shdr) * eHdr->e_shstrndx)];
    // if (!is_within_file_range(file->ptr, (void *)shStrTab)) {
    //     ft_putstr_fd("Error while parsing file->ptr\n", 2);
    //     return 1;
    // }

    const char *shStrTab_data = (const char *)(file->ptr + shStrTab->sh_offset);
    // if (!is_within_file_range(file->ptr, (void *)shStrTab_data)) {
    //     ft_putstr_fd("Error while parsing file->ptr\n", 2);
    //     return 1;
    // }
    for (int i = 0; i < eHdr->e_shnum; i++) {
        const long unsigned int sHdr_offset = eHdr->e_shoff + (sizeof(Elf64_Shdr) * i);
        if (sHdr_offset >= (long unsigned int)file->size) {
            return NULL;
        }
        Elf64_Shdr *sHdr = (Elf64_Shdr *)(file->ptr + sHdr_offset);
        // if (!is_within_file_range(file->ptr, (void *)sHdr)) {
        //     return -1;
        // }
        const char *section_name = shStrTab_data + sHdr->sh_name;
        // if (!is_within_file_range(file->ptr, (void *)section_name)) {
        //     return -1;
        // }
        // printf(" [%2d] : %s\n", i, section_name);
        if (ft_strncmp((const uint8_t *)section_name, (const uint8_t *)".text", ft_strlen(".text")) == 0) {
            printf("%s found at index %d\n", section_name, i);
            print_shdr(sHdr);
            return sHdr;
        }
    }
    return NULL;
}

Elf64_Phdr *find_pt_load_phdr(t_file *file, const Elf64_Ehdr *eHdr) {
    for(uint16_t i = 0; i < eHdr->e_phnum; i++) {
        Elf64_Phdr *pHdr = (Elf64_Phdr *)(file->ptr + eHdr->e_phoff + i * eHdr->e_phentsize);
        if (eHdr->e_phoff + i * eHdr->e_phentsize > (long unsigned int)file->size + eHdr->e_phentsize) {
            fprintf(stderr, "woody: Incorrect file provided\n");
            return NULL;
        }
        if (pHdr->p_flags == (PF_X | PF_R)) {
            print_phdr(pHdr);
            puts("FOUND PT_LOAD IN ELF FILE");
            return pHdr;
        }
    }
    fprintf(stderr, "woody: Coulnd't find PT_LOAD section in file %s, aborting\n ", file->path);
    return NULL;
}

Elf64_Phdr *find_pt_note_phdr(t_file *file, const Elf64_Ehdr *eHdr) {
    for(uint16_t i = 0; i < eHdr->e_phnum; i++) {
        Elf64_Phdr *pHdr = (Elf64_Phdr *)(file->ptr + eHdr->e_phoff + i * eHdr->e_phentsize);
        if (eHdr->e_phoff + i * eHdr->e_phentsize > (long unsigned int)file->size + eHdr->e_phentsize) {
            fprintf(stderr, "woody: Incorrect file provided\n");
            return NULL;
        }
        if (pHdr->p_type == PT_NOTE) {
            return pHdr;
        }
    }
    fprintf(stderr, "woody: Coulnd't find PT_NOTE section in file %s, aborting\n ", file->path);
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

    file->path = (uint8_t *)file_name;

    file->fd = open(file_name, O_RDWR);
    if (file->fd == -1) {
        fprintf(stderr, "woody: Can't open file\n");
        free(file);
        return NULL;
    }

    file->size = lseek(file->fd, 0, SEEK_END);
    if (file->size == (off_t) -1 || file->size < 50) {
        fprintf(stderr, "woody: Can't seek file\n");
        free(file);
        return NULL;
    }

    file->ptr = mmap(0, file->size, PROT_READ | PROT_WRITE, MAP_SHARED, file->fd, 0);
    if (file->ptr == (void *) -1) {
        fprintf(stderr, "woody: Can't mmap file\n");
        free(file);
        return NULL;
    }

    return file;
}

uint8_t *generate_key() {
    uint8_t *key = malloc(sizeof(uint8_t) * 64);
    if (key == NULL) {
        fprintf(stderr, "woody: can't generate key");
        return NULL;
    }

    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "woody: can't generate key");
        return NULL;
    }
    int red = read(fd, key, 64);
    if (red != 64) {
        fprintf(stderr, "woody: can't generate key");
        return NULL;
    }
    puts("Key is :");
    for (int i = 0; i < 64; i++) {
        printf("0x%x, ", key[i]);
    }
    puts("");
    for (int i = 0; i < 64; i++) {
        printf("%c", key[i]);
    }
    puts("");
    return key;
}

bool is_already_infected(t_file *file) {
    if (ft_strncmp(&file->ptr[file->size - 14], (const uint8_t *)"....WOODY....\n", 14) == 0) {
        return true;
    }
    return false;
}