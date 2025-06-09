#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

 /*@null@*/ char* int8_to_binary(int8_t n) {
    const uint8_t width = 8;
    char* binary_str = (char*)malloc(width + 1);
    if (binary_str == NULL) {
        return NULL;
    }

    // Startx# from the end of the array (MSB of binary representation)
    for (int i = width - 1; i >= 0; i--) {
        // Check if bit is set using bitwise AND with 1
        binary_str[width - 1 - i] = (n & (1 << i)) ? '1' : '0';
    }
    binary_str[width] = '\0';  // Add NULL terminator to end of char array
    return binary_str;
}

int main() {
    int8_t a = 2;
    int8_t not_a = ~a;

    char* a_bin = int8_to_binary(a);
    char* not_a_bin = int8_to_binary(not_a);

    printf("a = %d, binary: %s\n", a, a_bin);
    printf("~a = %d, binary: %s\n", not_a, not_a_bin);

    free(a_bin);
    free(not_a_bin);

    return 0;
}
