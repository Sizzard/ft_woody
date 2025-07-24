extern void print_proc_map();

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

int main(void) {
    // print_proc_map();
    uint64_t address;
    char buffer[13] = {0};
    int fd = open("/proc/self/maps", O_RDONLY);
    read(fd, buffer, sizeof(buffer) - 1);
    address = strtol(buffer, NULL, 16);
    printf("%s and %x\n", buffer, address);
}