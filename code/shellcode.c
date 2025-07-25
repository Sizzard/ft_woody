// extern uint64_t get_proc_value();

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

extern uint64_t get_proc_value();
// uint64_t get_proc_value() {
//     uint64_t address;
//     char buffer[13] = {0};
//     int fd = open("/proc/self/maps", O_RDONLY);
//     read(fd, buffer, sizeof(buffer) - 1);
//     address = strtol(buffer, NULL, 16);
//     // printf("%s and %lx\n", buffer, address);
//     return address;
// }

uint64_t strtox() {
    char buf[13];
    uint64_t res;
    int fd;
    int i;

    buf[12] = 0;
    fd = open("/proc/self/maps", O_RDONLY);

    read(fd, buf, 12);

    // printf("%s\n", buf);

    i = 0;
    res = 0;

    while (buf[i]) {

        res *= 16;

        if (buf[i] < 58) {

            res += buf[i];
            res -= 48;

        }
        else {

            res += buf[i];
            res-= 87;

        }
        i++;
    }

    return res;
}

int main(void) {
    printf("%lx\n", get_proc_value());
    // printf("%lx\n", strtox());
}