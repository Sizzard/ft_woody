#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void swap(unsigned char *a, unsigned char *b) {
    unsigned char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void rc4_encrypt(unsigned char *K, unsigned char *text) {
    unsigned char S[256];
    for (int i = 0; i < 256; i++) {
        // printf("%d, ", i);
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
    for(int i = 0; i < 388; i++) {
        text[i] = text[i] ^ S[i];
        printf("%d, ", text[i]);
    }
    puts("");
    for(int i = 0; i < 388; i++) {
        unsigned char decrypted = text[i] ^ S[i];
        printf("%c", decrypted);
    }
}

int main(void) {
    
    unsigned char key[256];
    unsigned char text[] = "Ceci est un texte totalement normalCeci est un texte totalement normalCeci est un texte totalement normalCeci est un texte totalement normalCeci est un texte totalement normalCeci est un texte totalement normalCeci est un texte totalement normalCeci est un texte totalement normalCeci est un texte totalement normalCeci est un texte totalement normalCeci est un texte totalement normale\n";

    int fd = open("/dev/random", O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "woody: can't open /dev/random");
        return 1;
    }
    int red = read(fd, key, 256);
    if (red != 256) {
        fprintf(stderr, "woody: can't read /dev/random");
        return 1;
    }
    puts("Key is :");
    for (int i = 0; i < 256; i++) {
        printf("%c", key[i]);
    }
    puts("\nEncrypted text is :");
    rc4_encrypt(key, text);
}