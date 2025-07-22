#include "woody.h"

bool handle_file(uint8_t *file) {
    const Elf64_Ehdr *eHdr = (Elf64_Ehdr *)file;
    print_ehdr(eHdr);
    return true;
}

void print_woody() {
    write(1, "....WOODY.....\n", 16); 
}


int main(int ac, char **av) {
    uint8_t *file;

    if (ac != 2) {
        fprintf(stderr, "woody: No argument provided\n");
        return 1;
    }

    file = open_file(av[1]);

    if (file == NULL) {
        return 1;
    }

    handle_file(file);

    return 0;
}
