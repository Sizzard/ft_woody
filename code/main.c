#include "woody.h"

bool handle_file(t_file *file) {
    Elf64_Ehdr *eHdr = (Elf64_Ehdr *)file->ptr;
    Elf64_Phdr *pHdr, *plHdr;
    uint64_t og_entry =  eHdr->e_entry;
    
    if (eHdr->e_type == ET_EXEC) {
        puts("No PIE detected");
        file->pie = false;
    }
    else if (eHdr->e_type == ET_DYN){
        puts("PIE detected");
        file->pie = true;
    }
    else {
        fprintf(stderr, "woody: file format not recognized\n");
        return ERROR;
    }
    // print_ehdr(eHdr);
    // print_all_phdr(file, eHdr);
    printf("ENTRY POINT = 0x%08lx\n", eHdr->e_entry);
    // printf(" and = 0x%04lx\n", (uint64_t)file->ptr[eHdr->e_entry]);
    plHdr = find_pt_load_phdr(file, eHdr);
    pHdr = find_pt_note_phdr(file, eHdr);
    if (pHdr == NULL || plHdr == NULL) {
        return ERROR;
    }

    file->key =  generate_key();
    if (file->key == NULL) {
        return ERROR;
    }
    puts("Found PT_NOTE pHdr and PT_load pHdr");
    // print_phdr(pHdr);

    hijack_phdr(file, eHdr, pHdr, plHdr);

    const Elf64_Shdr *shdr = find_texttab(file, eHdr);
    if (shdr == NULL) {
        fprintf(stderr, "woody: no .text section in file provided\n");
        return 1;
    }
    
    if (file->pie == false) {
        append_payload_no_pie(file, og_entry, shdr->sh_size);
    }
    else {
        append_payload_pie(file, og_entry, shdr->sh_size);
    }

    encrypt(file->key, &file->ptr[shdr->sh_offset], shdr->sh_size);
    return 0;
}

void cleanup_file(t_file *file) {

    munmap(file->ptr, file->size);

    if (file->key) {
        free(file->key);
    }
    free(file);

}

int main(int ac, char **av) {
    t_file *file;

    if (ac != 2) {
        fprintf(stderr, "woody: No argument provided\n");
        return 1;
    }

    file = open_file(av[1]);

    if (file == NULL) {
        return 1;
    }
    else if (is_already_infected(file)) {
        fprintf(stderr, "woody: File already infected\n");
        return 1;
    }

    handle_file(file);

    cleanup_file(file);

    return 0;
}
