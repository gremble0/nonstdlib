#include <stdint.h>
#include <stdio.h>

extern uint32_t djb2(char *key, uint32_t key_size);

int main() {
    printf("hello world %d\n", djb2("yo", 2));
}
