#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void encrypt (uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /* set up */
    uint32_t delta=0x9E3779B9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

void decrypt (uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up; sum is (delta << 5) & 0xFFFFFFFF */
    uint32_t delta=0x9E3779B9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        sum -= delta;
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

int main(void) {
    char buffer[8] = {0};
    uint32_t key[4] = {331172730, 1229588391, 676941200, 210081582};

    int fd = open("test.txt", O_RDWR);
    int red = read(fd, buffer, sizeof(buffer));
    while((red = read(fd, buffer, sizeof(buffer))) > 0) {
        printf("red : %d\n", red);
        printf("Buffer : %s\n", buffer);
        encrypt((uint32_t *)buffer, key);
        printf("Encrypted : %s\n", buffer);
        decrypt((uint32_t *)buffer, key);
        printf("Decrypted %s\n", buffer);
    }
}