// extern uint64_t get_proc_value();

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>

// extern uint64_t get_proc_value();
// extern void encrypt(unsigned char *text, size_t size);
extern void decrypt_test();
// extern void woody();
// extern void lil_encrypt(uint8_t *text, size_t size);
// extern void test_db();

// void dcrypt() {
//     char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor i";
//     encrypt(text, 256);
//     puts("\nEncrypted: ");
//     write(1, text, 256);
//     encrypt(text, 256);
//     puts("\nDecrypted :");
//     write(1, text, 256);
// }

// void test_caca() {
//     test_db();
// }
// uint64_t get_proc_value() {
//     uint64_t address;
//     char buffer[13] = {0};
//     int fd = open("/proc/self/maps", O_RDONLY);
//     read(fd, buffer, sizeof(buffer) - 1);
//     address = strtol(buffer, NULL, 16);
//     // printf("%s and %lx\n", buffer, address);
//     return address;
// }

// uint64_t strtox() {
//     char buf[13];
//     uint64_t res;
//     int fd;
//     int i;

//     buf[12] = 0;
//     fd = open("/proc/self/maps", O_RDONLY);

//     read(fd, buf, 12);

//     // printf("%s\n", buf);

//     i = 0;
//     res = 0;

//     while (buf[i]) {

//         res *= 16;

//         if (buf[i] < 58) {

//             res += buf[i];
//             res -= 48;

//         }
//         else {

//             res += buf[i];
//             res-= 87;

//         }
//         i++;
//     }

//     return res;
// }

// void lil_enc() {
//     unsigned char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor i";
//     lil_encrypt(text, sizeof(text));
//     puts("ENCRYPTED TEXT");
//     write(1, text, sizeof(text));
//     lil_encrypt(text, sizeof(text));
//     puts("\nDECRYPTED TEXT");
//     write(1, text, sizeof(text));
// }

int main(void) {
    // printf("%lx\n", get_proc_value());
    // dcrypt();
    decrypt_test();
    // int *test = NULL;
    // mprotect(test, 4, PROT_READ | PROT_WRITE | PROT_EXEC);
    // lil_enc();
    // woody();
    // test_caca();
    // printf("%lx\n", strtox());
}