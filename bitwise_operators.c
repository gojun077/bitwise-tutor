/*
bitwise_operators.c
Taken from Geeks for Geeks, edited by gopeterjun@naver.com

Created on: Sat 07 Jun 2025
Last Updated: Sun 08 Jun 2025

Examples for using bitwise operators in C
*/

#include <assert.h>
#include <stdio.h>
#include <stdint.h>  // for fixed-width int types
#include <stdlib.h>
#include <string.h>

// convert unsigned int to its binary representation as char array
/*@null@*/ char* uint_to_binary(uint8_t n, uint8_t width) {
    // allocate memory for string 'binary_str'
    char* binary_str = (char*)malloc(width+1);
    if (binary_str == NULL) {
        return NULL;
    }

    // start from the end of the array (MSB of binary representation)
    // i.e. left-most digit of binary number
    for (int i = width - 1; i >= 0; i--) {
        // current bit & 1 (bitwise AND)
        binary_str[i] = (n&1) ? '1' : '0';
        // bitwise right-shift 'n' by 1 place
        n >>= 1;
    }
    binary_str[width] = '\0';  // add NULL terminator to end of char array
    return binary_str;
}

// convert signed int to its binary representation as char array
// this will be used for 'bitwise complement' which sometimes can
// return negative values

/*@null@*/ char* int_to_binary(int8_t n, uint8_t width) {
    char* binary_str = (char*)malloc(width+1);
    if (binary_str == NULL) {
        return NULL;
    }
    // start from the end of the array (MSB of binary representation)
    // i.e. left-most digit of binary number
    for (int i = width - 1; i >= 0; i--) {
        // current bit & 1 (bitwise AND)
        binary_str[i] = (n&1) ? '1' : '0';
        // bitwise right-shift 'n' by 1 place
        n >>= 1;
    }
    binary_str[width] = '\0';  // add NULL terminator to end of char array
    return binary_str;
}

int main() {
    // a = 5 (00000101 in 8-bit binary)
    // b = 9 (00001001 in 8-bit binary)

    // later we need to take the bitwise complement of 'a'
    // but an unsigned int's complement can never be negative!
    // therefore we will define 'a' as signed 8-bit int
    int8_t a = 5;
    int8_t c = 2;
    // operations on 'b' will never return negative int, so we will
    // declare 'b' as unsigned int (always positive)
    uint8_t b = 9;
    uint8_t width = 8;
    char* binary_a = int_to_binary(a, width);
    char* binary_b = uint_to_binary(b, width);
    char* binary_c = int_to_binary(c, width);

    if (binary_a != NULL) {
        printf("a=%i base 10 in base 2 is %s\n", a, binary_a);
    } else {
        printf("creating char array failed");
    }

    if (binary_b != NULL) {
        printf("b=%u base 10 in base 2 is %s\n", b, binary_b);
    } else {
        printf("creating char array failed");
    }

    if (binary_c != NULL) {
        printf("c=%i base 10 in base 2 is %s\n", c, binary_c);
    } else {
        printf("creating char array failed");
    }

    char* binary_a_and_b = uint_to_binary(a&b, width);
    char* binary_a_or_b = uint_to_binary(a|b, width);
    char* binary_a_xor_b = uint_to_binary(a^b, width);
    int8_t not_a = ~a;
    int8_t not_c = ~c;
    char* binary_not_a = int_to_binary(not_a, width);
    char* binary_not_c = int_to_binary(not_c, width);
    char* binary_b_left = uint_to_binary(b<<1, width);
    char* binary_b_right = uint_to_binary(b>>1, width);

    // Add assert statements to check correctness
    assert((a & b) == 1);      // 5 & 9 == 1
    assert((a | b) == 13);     // 5 | 9 == 13
    assert((a ^ b) == 12);     // 5 ^ 9 == 12
    assert(not_a == -6);       // ~5 == -6 (int8_t not_a)
    assert(not_c == -3);       // ~2 == -3 (int8_t not_c)
    assert((b << 1) == 18);    // 9 << 1 == 18
    assert((b >> 1) == 4);     // 9 >> 1 == 4

    // The result is 2#00000001, 1
    printf("a&b = %u base-10\n", a & b);
    printf("a&b = %s binary\n", binary_a_and_b);

    // The result is 2#00001101, 13
    printf("a|b = %u base-10\n", a | b);
    printf("a|b = %s binary\n", binary_a_or_b);

    // The result is 2#00001100, 12
    printf("a^b = %u base-10\n", a ^ b);
    printf("a^b = %s binary\n", binary_a_xor_b);

    // The result is 2#11111010, -6
    printf("~a = %i base-10\n", not_a);
    printf("~a = %s binary\n", binary_not_a);
    printf("This might be a non-intuitive result: '6' in 8-bit binary: '00000110'\n");
    printf("Why, then, is '-6' in 8-bit binary: '11111010'?\n");
    printf("This is because negative numbers are stored as *2's complement*\n");
    printf("First flip all the bits in '00000110' -> '11111001'\n");
    printf("Finally add '1' to the result: '11111010'\n");
    printf("=================================\n");

    printf("~c = %i base-10\n", not_c);
    printf("~c = %s binary\n", binary_not_c);

    // The result is 00010010
    printf("b<<1 = %u base-10\n", b << 1);
    printf("b<<1 = %s binary\n", binary_b_left);

    // The result is 00000100
    printf("b>>1 = %u base-10\n", b >> 1);
    printf("b>>1 = %s binary\n", binary_b_right);

    // Memory allocated to char arrays above is freed below:
    free(binary_a);
    free(binary_b);
    free(binary_c);
    free(binary_a_and_b);
    free(binary_a_or_b);
    free(binary_a_xor_b);
    free(binary_not_a);
    free(binary_not_c);
    free(binary_b_left);
    free(binary_b_right);
    return 0;
}
