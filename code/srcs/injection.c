#include "../woody.h"

void hijack_phdr(t_file *file, Elf64_Ehdr *eHdr, Elf64_Phdr *pHdr) {
    pHdr->p_type = PT_LOAD;
    pHdr->p_flags = PF_R | PF_X;
    pHdr->p_vaddr = 0xc000000 + file->size;
    pHdr->p_filesz += PAYLOAD_SIZE;
    pHdr->p_memsz += PAYLOAD_SIZE;
    pHdr->p_offset = file->size;
    eHdr->e_entry = pHdr->p_vaddr;
}

bool append_payload(t_file *file, uint64_t og_entry) {
    unsigned char payload[56] = {0xbf, 0x01, 0x00, 0x00, 0x00, 0x48, 0x8d, 0x35, 0x1e, 0x00, 0x00, 0x00, 0xba, 0x0e, 0x00, 0x00, 0x00, 0xb8, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x05, 0x48, 0x31, 0xff, 0x48, 0x31, 0xd2, 0x48, 0xb8, 0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12, 0xff, 0xe0, 0x2e, 0x2e, 0x2e, 0x2e, 0x57, 0x4f, 0x4f, 0x44, 0x59, 0x2e, 0x2e, 0x2e, 0x2e, 0x0a};
    int ret;

    printf("Copying 0x%04lX into shellcode\n", og_entry);
    memcpy(payload + 32, &og_entry, 8);

    lseek(file->fd, 0, SEEK_END);
    ret = write(file->fd, payload, sizeof(payload));
    printf("Wrote : %d/%ld bytes into %s\n", ret, sizeof(payload), file->path);
    if (ret > 0) {
        printf("Payload successfully injected at 0x%lx --- %ld\n", file->size, file->size);
    }
    else {
        fprintf(stderr, "Couldn't inject payload\n");
    }
    return ret;
}