#include "../woody.h"

void encrypt(uint8_t *K, uint8_t *text, size_t size) {

    puts("\nEncrypted .text section :");
    for(size_t i = 0, j = 0; i < size; i++) {
        j = i % 64;
        text[i] ^= K[j];
        printf("%c", text[i]);
    }
    for(size_t i = 0, j = 0; i < size; i++) {
        j = i % 64;
        text[i] ^= K[j];
        printf("%c", text[i]);
    }
}
