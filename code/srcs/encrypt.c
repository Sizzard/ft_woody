#include "../woody.h"

void swap(unsigned char *a, unsigned char *b) {
    unsigned char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void rc4_encrypt(unsigned char *K, unsigned char *text, size_t size) {
    unsigned char S[256];
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    for (int i, j = 0; i < 256; i++) {
        j = (j + S[i] + K[i]) % 256;
        swap(&S[i], &S[j]);
    }
    for(int idx, i, j = 0; idx < 256; idx++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(&S[i], &S[j]);
    }
    for(size_t i = 0; i < size; i++) {
        text[i] = text[i] ^ S[i];
        // printf("%d, ", text[i]);
    }
    // for(size_t i = 0; i < size; i++) {
    //     text[i] = text[i] ^ S[i];
    // }
}

int encrypt(t_file *file, size_t text_offset, size_t text_size) {
    unsigned char key[256];
    uint8_t *text_section = &file->ptr[text_offset];

    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "woody: can't open /dev/urandom");
        return 1;
    }
    int red = read(fd, key, 256);
    if (red != 256) {
        fprintf(stderr, "woody: can't read /dev/urandom");
        return 1;
    }
    puts("Key is :");
    for (int i = 0; i < 256; i++) {
        printf("0x%x, ", key[i]);
    }
    puts("Encrypted .text section :");
    rc4_encrypt(key, text_section, text_size);
    return 0;
}