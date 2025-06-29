/*
 * bwt.c - Bitwise Tutor
 * Created on: Mon 09 Jun 2025
 * Last Updated: Sun 29 Jun 2025
 * Author: Various LLM's and gopeterjun@naver.com
 *
 * This is the Proof of Concept (Alpha) implementation of the bitwise-tutor
 * program which quizzes students on binary representation and bitwise operations
 * in the C programming language.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

// Function prototypes
/*@null@*/ char* uint8_to_binary(uint8_t n);
/*@null@*/ char* uint16_to_binary(uint16_t n);
/*@null@*/ char* uint32_to_binary(uint32_t n);
/*@null@*/ char* int8_to_binary(int8_t n);
/*@null@*/ char* int16_to_binary(int16_t n);
/*@null@*/ char* int32_to_binary(int32_t n);
bool validate_binary_input(const char* input, uint8_t width);
void free_if_not_null(char* ptr);
void clear_input_buffer(void);
void run_bitwise_and_quiz(void);
void run_bitwise_or_quiz(void);
void run_bitwise_xor_quiz(void);
void run_bitwise_not_quiz(void);
void run_shift_quiz(void);
void run_binary_decimal_conversion_quiz(void);
bool get_binary_input(char* buffer, size_t buffer_size, uint8_t expected_width);
int binary_to_int(const char* binary_str);

/**
 * Convert 8-bit unsigned integer to binary representation
 *
 * @param n The unsigned 8-bit integer to convert
 * @return A dynamically allocated string with binary representation (caller must free)
 */
char* uint8_to_binary(uint8_t n) {
    const uint8_t width = 8;
    char* binary_str = (char*)malloc(width + 1);
    if (binary_str == NULL) {
        return NULL;
    }

    // Start from the end of the array (MSB of binary representation)
    for (int i = width - 1; i >= 0; i--) {
        // Check if bit is set using bitwise AND with 1
        binary_str[width - 1 - i] = (n & (1 << i)) ? '1' : '0';
    }
    binary_str[width] = '\0';  // Add NULL terminator to end of char array
    return binary_str;
}

/**
 * Convert 16-bit unsigned integer to binary representation
 *
 * @param n The unsigned 16-bit integer to convert
 * @return A dynamically allocated string with binary representation (caller must free)
 */
char* uint16_to_binary(uint16_t n) {
    const uint8_t width = 16;
    char* binary_str = (char*)malloc(width + 1);
    if (binary_str == NULL) {
        return NULL;
    }

    // Start from the end of the array (MSB of binary representation)
    for (int i = width - 1; i >= 0; i--) {
        // Check if bit is set using bitwise AND with 1
        binary_str[width - 1 - i] = (n & (1 << i)) ? '1' : '0';
    }
    binary_str[width] = '\0';  // Add NULL terminator to end of char array
    return binary_str;
}

/**
 * Convert 32-bit unsigned integer to binary representation
 *
 * @param n The unsigned 32-bit integer to convert
 * @return A dynamically allocated string with binary representation (caller must free)
 */
char* uint32_to_binary(uint32_t n) {
    const uint8_t width = 32;
    char* binary_str = (char*)malloc(width + 1);
    if (binary_str == NULL) {
        return NULL;
    }

    // Start from the end of the array (MSB of binary representation)
    for (int i = width - 1; i >= 0; i--) {
        // Check if bit is set using bitwise AND with 1
        binary_str[width - 1 - i] = (n & (1UL << i)) ? '1' : '0';
    }
    binary_str[width] = '\0';  // Add NULL terminator to end of char array
    return binary_str;
}

/**
 * Convert 8-bit signed integer to binary representation
 *
 * @param n The signed 8-bit integer to convert
 * @return A dynamically allocated string with binary representation (caller must free)
 */
char* int8_to_binary(int8_t n) {
    const uint8_t width = 8;
    char* binary_str = (char*)malloc(width + 1);
    if (binary_str == NULL) {
        return NULL;
    }

    // Start from the end of the array (MSB of binary representation)
    for (int i = width - 1; i >= 0; i--) {
        // Check if bit is set using bitwise AND with 1
        binary_str[width - 1 - i] = (n & (1 << i)) ? '1' : '0';
    }
    binary_str[width] = '\0';  // Add NULL terminator to end of char array
    return binary_str;
}

/**
 * Convert 16-bit signed integer to binary representation
 *
 * @param n The signed 16-bit integer to convert
 * @return A dynamically allocated string with binary representation (caller must free)
 */
char* int16_to_binary(int16_t n) {
    const uint8_t width = 16;
    char* binary_str = (char*)malloc(width + 1);
    if (binary_str == NULL) {
        return NULL;
    }

    // Start from the end of the array (MSB of binary representation)
    for (int i = width - 1; i >= 0; i--) {
        // Check if bit is set using bitwise AND with 1
        binary_str[width - 1 - i] = (n & (1 << i)) ? '1' : '0';
    }
    binary_str[width] = '\0';  // Add NULL terminator to end of char array
    return binary_str;
}

/**
 * Convert 32-bit signed integer to binary representation
 *
 * @param n The signed 32-bit integer to convert
 * @return A dynamically allocated string with binary representation (caller must free)
 */
char* int32_to_binary(int32_t n) {
    const uint8_t width = 32;
    char* binary_str = (char*)malloc(width + 1);
    if (binary_str == NULL) {
        return NULL;
    }

    // Start from the end of the array (MSB of binary representation)
    for (int i = width - 1; i >= 0; i--) {
        // Check if bit is set using bitwise AND with 1
        binary_str[width - 1 - i] = (n & (1L << i)) ? '1' : '0';
    }
    binary_str[width] = '\0';  // Add NULL terminator to end of char array
    return binary_str;
}

/**
 * Validate binary input from user
 *
 * @param input The string to validate
 * @param width The expected width of the binary string
 * @return true if input is valid binary representation, false otherwise
 */
bool validate_binary_input(const char* input, uint8_t width) {
    if (input == NULL) {
        return false;
    }

    // Check if length matches expected width
    if (strlen(input) != width) {
        return false;
    }

    // Check if all characters are '0' or '1'
    for (size_t i = 0; i < width; i++) {
        if (input[i] != '0' && input[i] != '1') {
            return false;
        }
    }

    return true;
}

/**
 * Free memory if pointer is not NULL
 *
 * @param ptr Pointer to free
 */
void free_if_not_null(char* ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}

/**
 * Clear input buffer to prevent issues with scanf
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Get binary input from user with validation
 *
 * @param buffer Buffer to store input
 * @param buffer_size Size of buffer
 * @param expected_width Expected width of binary string
 * @return true if input is valid, false otherwise
 */
bool get_binary_input(char* buffer, size_t buffer_size, uint8_t expected_width) {
    printf(">>> ");
    if (fgets(buffer, buffer_size, stdin) == NULL) {
        return false;
    }

    // Remove newline character if present
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    // Check if input contains only digits
    for (size_t i = 0; i < len; i++) {
        if (buffer[i] != '0' && buffer[i] != '1') {
            printf("Please enter digits only.\n");
            return false;
        }
    }

    // Check if input has correct length
    if (len != expected_width) {
        return false;
    }

    return true;
}

/**
 * Convert binary string to integer
 *
 * @param binary_str Binary string to convert
 * @return Integer value
 */
int binary_to_int(const char* binary_str) {
    int result = 0;
    size_t len = strlen(binary_str);

    for (size_t i = 0; i < len; i++) {
        result = result << 1;
        if (binary_str[i] == '1') {
            result = result | 1;
        }
    }

    return result;
}

/**
 * Run a quiz on bitwise AND operation
 */
void run_bitwise_and_quiz(void) {
    // Generate two random 8-bit integers
    //int8_t a = rand() % 16;  // Small values for easier understanding
    //int8_t b = rand() % 16;
    int8_t a = rand();
    int8_t b = rand();

    char* a_bin = int8_to_binary(a);
    char* b_bin = int8_to_binary(b);
    char* result_bin = int8_to_binary(a & b);

    // Quiz: Decimal to Binary
    printf("\nThe following questions are about signed 8-bit integers *a* and *b*.\n");
    printf("Given `a=%d` and `b=%d`,\n\n", a, b);

    // Question 1: Binary representation of a
    printf("Q1: What is the binary representation of `%d`?\n", a);

    char user_input[100];
    bool correct = false;

    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, a_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Question 2: Binary representation of b
    printf("Q2: What is the binary representation of `%d`?\n", b);

    correct = false;
    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, b_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Question 3: Result of a&b in binary
    printf("Q3: What is the result of `a&b` in binary?\n");

    correct = false;
    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, result_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Question 4: Result of a&b in decimal
    printf("Q4: What is the result of `a&b` in decimal?\n");

    int result_dec = a & b;
    int user_dec;

    correct = false;
    while (!correct) {
        printf(">>> ");
        if (scanf("%d", &user_dec) == 1) {
            if (user_dec == result_dec) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter a decimal number.\n\n");
            clear_input_buffer();
        }
    }

    // Clean up
    free_if_not_null(a_bin);
    free_if_not_null(b_bin);
    free_if_not_null(result_bin);
    clear_input_buffer();
}
/**
 * Run a quiz on bitwise XOR operation
 */
void run_bitwise_xor_quiz(void) {
    // Generate two random 8-bit integers
    int8_t a = rand();
    int8_t b = rand();

    char* a_bin = int8_to_binary(a);
    char* b_bin = int8_to_binary(b);
    char* result_bin = int8_to_binary(a ^ b);

    // Quiz: Decimal to Binary
    printf("\nThe following questions are about signed 8-bit integers *a* and *b*.\n");
    printf("Given `a=%d` and `b=%d`,\n\n", a, b);

    // Question 1: Binary representation of a
    printf("Q1: What is the binary representation of `%d`?\n", a);

    char user_input[100];
    bool correct = false;

    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, a_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Question 2: Binary representation of b
    printf("Q2: What is the binary representation of `%d`?\n", b);

    correct = false;
    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, b_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Question 3: Result of a^b in binary
    printf("Q3: What is the result of `a^b` in binary?\n");

    correct = false;
    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, result_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Question 4: Result of a^b in decimal
    printf("Q4: What is the result of `a^b` in decimal?\n");

    int result_dec = a ^ b;
    int user_dec;

    correct = false;
    while (!correct) {
        printf(">>> ");
        if (scanf("%d", &user_dec) == 1) {
            if (user_dec == result_dec) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter a decimal number.\n\n");
            clear_input_buffer();
        }
    }

    // Clean up
    free_if_not_null(a_bin);
    free_if_not_null(b_bin);
    free_if_not_null(result_bin);
    clear_input_buffer();
}
/**
 * Run a quiz on bitwise OR operation
 */
void run_bitwise_or_quiz(void) {
    // Generate two random 8-bit integers
    int8_t a = rand();
    int8_t b = rand();

    char* a_bin = int8_to_binary(a);
    char* b_bin = int8_to_binary(b);
    char* result_bin = int8_to_binary(a | b);

    // Quiz: Decimal to Binary
    printf("\nThe following questions are about signed 8-bit integers *a* and *b*.\n");
    printf("Given `a=%d` and `b=%d`,\n\n", a, b);

    // Question 1: Binary representation of a
    printf("Q1: What is the binary representation of `%d`?\n", a);

    char user_input[100];
    bool correct = false;

    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, a_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Question 2: Binary representation of b
    printf("Q2: What is the binary representation of `%d`?\n", b);

    correct = false;
    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, b_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Question 3: Result of a|b in binary
    printf("Q3: What is the result of `a|b` in binary?\n");

    correct = false;
    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, result_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Question 4: Result of a|b in decimal
    printf("Q4: What is the result of `a|b` in decimal?\n");

    int result_dec = a | b;
    int user_dec;

    correct = false;
    while (!correct) {
        printf(">>> ");
        if (scanf("%d", &user_dec) == 1) {
            if (user_dec == result_dec) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter a decimal number.\n\n");
            clear_input_buffer();
        }
    }

    // Clean up
    free_if_not_null(a_bin);
    free_if_not_null(b_bin);
    free_if_not_null(result_bin);
    clear_input_buffer();
}

/**
 * Run a quiz with binary values first
 */
void run_binary_first_quiz(void) {
    // Use predefined binary values for demonstration
    const char* a_bin = "00001010";  // 10 in decimal
    const char* b_bin = "00001000";  // 8 in decimal

    int a_dec = binary_to_int(a_bin);
    int b_dec = binary_to_int(b_bin);
    char* result_bin = int8_to_binary(a_dec & b_dec);

    printf("\nThe following questions are about signed 8-bit integers *a* and *b*.\n");
    printf("Given `a=%s` and `b=%s` in binary,\n\n", a_bin, b_bin);

    // Question 1: a&b in binary
    printf("Q1: What is `a&b` in binary?\n");

    char user_input[100];
    bool correct = false;

    while (!correct) {
        if (fgets(user_input, sizeof(user_input), stdin) != NULL) {
            // Remove newline character if present
            size_t len = strlen(user_input);
            if (len > 0 && user_input[len - 1] == '\n') {
                user_input[len - 1] = '\0';
                len--;
            }

            // Check if input contains only digits and has correct length
            bool valid_input = true;
            if (len != 8) {
                valid_input = false;
            } else {
                for (size_t i = 0; i < len; i++) {
                    if (user_input[i] != '0' && user_input[i] != '1') {
                        printf("Please enter digits only.\n\n");
                        valid_input = false;
                        break;
                    }
                }
            }

            if (valid_input) {
                if (strcmp(user_input, result_bin) == 0) {
                    printf("Correct!\n\n");
                    correct = true;
                } else {
                    printf("Sorry, that is incorrect! Please try again\n\n");
                }
            }
        }
    }

    // Question 2: a in decimal
    printf("Q2: What is `a` in decimal?\n");

    int user_dec;
    correct = false;

    while (!correct) {
        printf(">>> ");
        if (scanf("%d", &user_dec) == 1) {
            if (user_dec == a_dec) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter a decimal number.\n\n");
            clear_input_buffer();
        }
    }

    // Question 3: b in decimal
    printf("Q3: What is `b` in decimal?\n");

    correct = false;

    while (!correct) {
        printf(">>> ");
        if (scanf("%d", &user_dec) == 1) {
            if (user_dec == b_dec) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter a decimal number.\n\n");
            clear_input_buffer();
        }
    }

    // Clean up
    free_if_not_null(result_bin);
    clear_input_buffer();
}

/**
 * Run a quiz on bitwise NOT operation to demonstrate the difference
 * between signed and unsigned integers
 *
 * Note on Two's Complement and Bitwise NOT:
 * 1. Two's complement is a way to represent negative numbers in binary.
 * 2. For a positive number, its negative equivalent in two's complement is obtained by:
 *    a) Inverting all bits (one's complement)
 *    b) Adding 1 to the result
 * 3. However, when we simply use the bitwise NOT operator (~), we're only performing
 *    the first step (inverting all bits).
 * 4. For example, to get -3 in two's complement from 2:
 *    - Start with 2: 00000010
 *    - Invert all bits: 11111101 (this is what ~ does)
 *    - This is already -3 in two's complement
 * 5. This works because ~x is equivalent to (-x - 1) in two's complement.
 *    So ~2 = -2 - 1 = -3
 */
void run_bitwise_not_quiz(void) {
    // Use a small value for demonstration
    int8_t signed_val = 2;
    uint8_t unsigned_val = 2;

    int8_t signed_not = ~signed_val;    // Should be -3
    uint8_t unsigned_not = ~unsigned_val; // Should be 253

    // Add assertions to verify our understanding
    assert(signed_not == -3);       // ~2 == -3 (int8_t signed_not)
    assert(unsigned_not == 253);    // ~2 == 253 (uint8_t unsigned_not)

    char* signed_bin = int8_to_binary(signed_val);
    char* unsigned_bin = uint8_to_binary(unsigned_val);
    char* signed_not_bin = int8_to_binary(signed_not);
    char* unsigned_not_bin = uint8_to_binary(unsigned_not);

    // Double-check that our binary conversion is correct
    char expected_signed_not_bin[9] = "11111101";  // Correct binary representation of -3
    assert(strcmp(signed_not_bin, expected_signed_not_bin) == 0);

    printf("\nThe following questions are about the bitwise NOT operator with different integer types.\n");
    printf("Given signed int `a=%d` and unsigned int `b=%u`,\n\n", signed_val, unsigned_val);

    // Show binary representations
    printf("a (signed) in binary: %s\n", signed_bin);
    printf("b (unsigned) in binary: %s\n\n", unsigned_bin);

    // Question 1: ~a (signed) in binary
    printf("Q1: What is `~a` in binary? (a is signed)\n");

    char user_input[100];
    bool correct = false;

    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, signed_not_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Question 2: ~a (signed) in decimal
    printf("Q2: What is `~a` in decimal? (a is signed)\n");

    int user_dec;
    correct = false;

    while (!correct) {
        printf(">>> ");
        if (scanf("%d", &user_dec) == 1) {
            if (user_dec == signed_not) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter a decimal number.\n\n");
            clear_input_buffer();
        }
    }

    // Question 3: ~b (unsigned) in binary
    printf("Q3: What is `~b` in binary? (b is unsigned)\n");

    clear_input_buffer();
    correct = false;

    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, unsigned_not_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Question 4: ~b (unsigned) in decimal
    printf("Q4: What is `~b` in decimal? (b is unsigned)\n");

    unsigned user_udec;
    correct = false;

    while (!correct) {
        printf(">>> ");
        if (scanf("%u", &user_udec) == 1) {
            if (user_udec == unsigned_not) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter a decimal number.\n\n");
            clear_input_buffer();
        }
    }

    // Explanation of two's complement
    printf("Did you notice the difference?\n");
    printf("~%d (signed) = %d, while ~%u (unsigned) = %u\n", signed_val, signed_not, unsigned_val, unsigned_not);
    printf("This is because negative numbers are stored using two's complement.\n");
    printf("For bitwise NOT (~) operation:\n");
    printf("1. When we apply ~ to a number, we simply flip all the bits.\n");
    printf("2. For unsigned integers, this just gives us the bitwise complement.\n");
    printf("3. For signed integers, the result is interpreted as a two's complement representation\n");
    printf("   of a negative number if the most significant bit is 1.\n");
    printf("\nTo verify: The binary representation of %d is %s\n", signed_val, signed_bin);
    printf("Applying ~ gives us %s (which is %d in decimal)\n", signed_not_bin, signed_not);
    printf("This matches our expectation since ~%d = %d for signed 8-bit integers.\n",
           signed_val, signed_not);

    // Clean up
    free_if_not_null(signed_bin);
    free_if_not_null(unsigned_bin);
    free_if_not_null(signed_not_bin);
    free_if_not_null(unsigned_not_bin);
    clear_input_buffer();
}

/**
 * Run a quiz on binary to decimal and decimal to binary conversions,
 * highlighting the differences between signed and unsigned integers
 */
void run_binary_decimal_conversion_quiz(void) {
    printf("\n=== Binary <--> Decimal Conversion Quiz ===\n");
    printf("This quiz will help you understand how the same binary pattern\n");
    printf("can represent different values as signed or unsigned integers.\n\n");

    int sub_choice;

    printf("Choose a sub-topic:\n");
    printf("1. Decimal to Binary conversions\n");
    printf("2. Binary to Decimal conversions\n");
    printf("3. Same binary, different interpretations\n");
    printf("Enter your choice (1-3): ");

    if (scanf("%d", &sub_choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        clear_input_buffer();
        return;
    }

    clear_input_buffer();

    switch (sub_choice) {
        case 1:
            // Decimal to Binary conversions
            {
                // Generate a random number for the quiz
                int8_t signed_val = rand() % 100 - 50;  // Range: -50 to 49
                uint8_t unsigned_val = (uint8_t)abs(signed_val);

                printf("\n=== Decimal to Binary Conversion ===\n");

                // Signed integer conversion
                printf("Q1: Convert the signed decimal %d to 8-bit binary representation.\n", signed_val);

                char* signed_bin = int8_to_binary(signed_val);
                char user_input[100];
                bool correct = false;

                while (!correct) {
                    if (get_binary_input(user_input, sizeof(user_input), 8)) {
                        if (strcmp(user_input, signed_bin) == 0) {
                            printf("Correct! %d in binary is %s\n\n", signed_val, signed_bin);
                            correct = true;
                        } else {
                            printf("Sorry, that is incorrect! Please try again\n\n");
                        }
                    } else {
                        printf("Invalid input. Please enter an 8-bit binary number.\n\n");
                    }
                }

                // Unsigned integer conversion
                printf("Q2: Convert the unsigned decimal %u to 8-bit binary representation.\n", unsigned_val);

                char* unsigned_bin = uint8_to_binary(unsigned_val);
                correct = false;

                while (!correct) {
                    if (get_binary_input(user_input, sizeof(user_input), 8)) {
                        if (strcmp(user_input, unsigned_bin) == 0) {
                            printf("Correct! %u in binary is %s\n\n", unsigned_val, unsigned_bin);
                            correct = true;
                        } else {
                            printf("Sorry, that is incorrect! Please try again\n\n");
                        }
                    } else {
                        printf("Invalid input. Please enter an 8-bit binary number.\n\n");
                    }
                }

                // Clean up
                free_if_not_null(signed_bin);
                free_if_not_null(unsigned_bin);
            }
            break;

        case 2:
            // Binary to Decimal conversions
            {
                // Choose a binary number that would be interpreted differently as signed vs unsigned
                // Start with a binary number that has a 1 in the most significant bit
                const char* binary_val = "10101010";  // 170 unsigned, -86 signed

                printf("\n=== Binary to Decimal Conversion ===\n");
                printf("Given the binary number: %s\n\n", binary_val);

                // Convert to unsigned
                uint8_t unsigned_val = 0;
                for (int i = 0; i < 8; i++) {
                    unsigned_val = (unsigned_val << 1) | (binary_val[i] - '0');
                }

                // Convert to signed
                int8_t signed_val = 0;
                for (int i = 0; i < 8; i++) {
                    signed_val = (signed_val << 1) | (binary_val[i] - '0');
                }

                // Question for unsigned
                printf("Q1: What is the decimal value of %s when interpreted as an unsigned 8-bit integer?\n", binary_val);

                unsigned int user_unsigned;
                bool correct = false;

                while (!correct) {
                    printf(">>> ");
                    if (scanf("%u", &user_unsigned) == 1) {
                        if (user_unsigned == unsigned_val) {
                            printf("Correct! %s as an unsigned integer is %u\n\n", binary_val, unsigned_val);
                            correct = true;
                        } else {
                            printf("Sorry, that is incorrect! Please try again\n\n");
                        }
                    } else {
                        printf("Invalid input. Please enter a decimal number.\n\n");
                        clear_input_buffer();
                    }
                }

                // Question for signed
                printf("Q2: What is the decimal value of %s when interpreted as a signed 8-bit integer?\n", binary_val);

                int user_signed;
                correct = false;

                clear_input_buffer();

                while (!correct) {
                    printf(">>> ");
                    if (scanf("%d", &user_signed) == 1) {
                        if (user_signed == signed_val) {
                            printf("Correct! %s as a signed integer is %d\n\n", binary_val, signed_val);
                            correct = true;
                        } else {
                            printf("Sorry, that is incorrect! Please try again\n\n");
                        }
                    } else {
                        printf("Invalid input. Please enter a decimal number.\n\n");
                        clear_input_buffer();
                    }
                }

                clear_input_buffer();
            }
            break;

        case 3:
            // Same binary, different interpretations
            {
                printf("\n=== Same Binary, Different Interpretations ===\n");
                printf("This quiz demonstrates how the same binary pattern can represent\n");
                printf("different values depending on whether it's interpreted as signed or unsigned.\n\n");

                // Use a few interesting binary patterns
                const char* binary_patterns[] = {
                    "10000000",  // -128 signed, 128 unsigned
                    "11111111",  // -1 signed, 255 unsigned
                    "10000001",  // -127 signed, 129 unsigned
                    "01111111"   // 127 signed, 127 unsigned
                };

                const int num_patterns = sizeof(binary_patterns) / sizeof(binary_patterns[0]);

                for (int i = 0; i < num_patterns; i++) {
                    const char* binary = binary_patterns[i];

                    // Convert to unsigned
                    uint8_t unsigned_val = 0;
                    for (int j = 0; j < 8; j++) {
                        unsigned_val = (unsigned_val << 1) | (binary[j] - '0');
                    }

                    // Convert to signed
                    int8_t signed_val = 0;
                    for (int j = 0; j < 8; j++) {
                        signed_val = (signed_val << 1) | (binary[j] - '0');
                    }

                    printf("Binary pattern: %s\n", binary);
                    printf("As unsigned 8-bit integer: %u\n", unsigned_val);
                    printf("As signed 8-bit integer: %d\n\n", signed_val);

                    // Only ask questions for the first two patterns
                    if (i < 2) {
                        // Question: Explain why the same binary can have different values
                        printf("Q%d: Why does the binary pattern %s represent different values?\n", i+1, binary);
                        printf("1. Because binary numbers are always ambiguous\n");
                        printf("2. Because the most significant bit is interpreted as the sign bit for signed integers\n");
                        printf("3. Because unsigned integers can only be positive\n");
                        printf("4. Because signed integers use a different counting system\n");

                        int answer;
                        bool correct = false;

                        while (!correct) {
                            printf("Enter your answer (1-4): ");
                            if (scanf("%d", &answer) == 1) {
                                if (answer == 2) {
                                    printf("Correct! In signed integers, the most significant bit (leftmost) is the sign bit.\n");
                                    printf("If it's 1, the number is negative and uses two's complement representation.\n");
                                    printf("In unsigned integers, all bits (including the most significant) represent magnitude.\n\n");
                                    correct = true;
                                } else {
                                    printf("Sorry, that is incorrect! Please try again\n\n");
                                }
                            } else {
                                printf("Invalid input. Please enter a number.\n\n");
                                clear_input_buffer();
                            }
                        }

                        clear_input_buffer();
                    }
                }

                // Final explanation
                printf("=== Key Insights ===\n");
                printf("1. The same binary pattern can have different decimal values depending on interpretation.\n");
                printf("2. For signed integers (using two's complement):\n");
                printf("   - If the most significant bit is 0, the number is positive.\n");
                printf("   - If the most significant bit is 1, the number is negative.\n");
                printf("3. For unsigned integers, all bits contribute to the magnitude.\n");
                printf("4. To convert a negative number to two's complement:\n");
                printf("   - Take the absolute value in binary\n");
                printf("   - Invert all bits (one's complement)\n");
                printf("   - Add 1 to the result\n");
                printf("5. Example: -5 in two's complement 8-bit binary:\n");
                printf("   - 5 in binary: 00000101\n");
                printf("   - Invert bits: 11111010\n");
                printf("   - Add 1:      11111011\n");
            }
            break;

        default:
            printf("Invalid choice. Returning to main menu.\n");
    }
}

/**
 * Run a quiz on bitwise shift operations (left-shift << and right-shift >>)
 */
void run_shift_quiz(void) {
    // Generate a small random unsigned 8-bit integer
    uint8_t a = rand() % 128; // keep it in 7 bits for easy observation
    uint8_t left_amt = 1 + rand() % 3; // left shift by 1, 2 or 3
    uint8_t right_amt = 1 + rand() % 3; // right shift by 1, 2 or 3

    char* a_bin = uint8_to_binary(a);

    printf("\nThe following questions are about shifting unsigned 8-bit integer a bitwise.\n");
    printf("Given a = %u\n", a);

    // Q1: What is the binary representation of a?
    printf("Q1: What is the binary representation of %u?\n", a);
    char user_input[100];
    bool correct = false;
    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, a_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Q2: What is the result of a << left_amt in binary?
    uint8_t left_val = a << left_amt;
    char* left_bin = uint8_to_binary(left_val);
    printf("Q2: What is the binary result of a << %u?\n", left_amt);
    correct = false;
    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, left_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Q3: What is the decimal result of a << left_amt?
    printf("Q3: What is the decimal result of a << %u?\n", left_amt);
    int user_dec;
    correct = false;
    while (!correct) {
        printf(">>> ");
        if (scanf("%d", &user_dec) == 1) {
            if ((uint8_t)user_dec == left_val) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter a decimal number.\n\n");
            clear_input_buffer();
        }
    }

    // Q4: What is the result of a >> right_amt in binary?
    uint8_t right_val = a >> right_amt;
    char* right_bin = uint8_to_binary(right_val);
    printf("Q4: What is the binary result of a >> %u?\n", right_amt);
    clear_input_buffer();
    correct = false;
    while (!correct) {
        if (get_binary_input(user_input, sizeof(user_input), 8)) {
            if (strcmp(user_input, right_bin) == 0) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter an 8-bit binary number.\n\n");
        }
    }

    // Q5: What is the decimal result of a >> right_amt?
    printf("Q5: What is the decimal result of a >> %u?\n", right_amt);
    correct = false;
    while (!correct) {
        printf(">>> ");
        if (scanf("%d", &user_dec) == 1) {
            if ((uint8_t)user_dec == right_val) {
                printf("Correct!\n\n");
                correct = true;
            } else {
                printf("Sorry, that is incorrect! Please try again\n\n");
            }
        } else {
            printf("Invalid input. Please enter a decimal number.\n\n");
            clear_input_buffer();
        }
    }

    free_if_not_null(a_bin);
    free_if_not_null(left_bin);
    free_if_not_null(right_bin);
    clear_input_buffer();
}


/**
 * Main function
 */
int main(void) {
    // Verify our implementations with assertions
    {
        // Test basic binary conversion
        uint8_t test_u8 = 42;
        char* test_bin = uint8_to_binary(test_u8);
        assert(strcmp(test_bin, "00101010") == 0);
        free_if_not_null(test_bin);

        // Test signed integers
        int8_t test_i8 = -42;
        test_bin = int8_to_binary(test_i8);
        assert(strcmp(test_bin, "11010110") == 0);
        free_if_not_null(test_bin);

        // Test bitwise operations
        uint8_t a = 5;   // 00000101
        uint8_t b = 9;   // 00001001

        assert((a & b) == 1);      // 5 & 9 == 1
        assert((a | b) == 13);     // 5 | 9 == 13
        assert((a ^ b) == 12);     // 5 ^ 9 == 12

        // Critical test cases for bitwise NOT
        int8_t signed_2 = 2;
        int8_t signed_not_2 = ~signed_2;
        assert(signed_not_2 == -3); // ~2 == -3 for signed int

        uint8_t unsigned_2 = 2;
        uint8_t unsigned_not_2 = ~unsigned_2;
        assert(unsigned_not_2 == 253); // ~2 == 253 for unsigned int

        int8_t signed_5 = 5;
        int8_t signed_not_5 = ~signed_5;
        assert(signed_not_5 == -6); // ~5 == -6 for signed int

        // Test shift operations
        assert((a << 1) == 10);    // 5 << 1 == 10
        assert((a >> 1) == 2);     // 5 >> 1 == 2
    }

    // Seed random number generator
    srand((unsigned int)time(NULL));

    printf("Welcome to Bitwise Tutor (bwt)!\n");
    printf("This program will help you practice bitwise operations and binary conversions.\n");
    printf("Let's get started!\n\n");

    int choice;
    bool running = true;

    while (running) {
printf("\nChoose a quiz type:\n");
        printf("1. Bitwise AND quiz (decimal values given)\n");
        printf("2. Bitwise quiz (binary values given)\n");
        printf("3. Bitwise XOR quiz (decimal values given)\n");
        printf("4. Bitwise OR quiz (decimal values given)\n");
        printf("5. Bitwise NOT quiz (signed vs unsigned)\n");
        printf("6. Binary <--> decimal conversions\n");
        printf("7. Bit-shift operations quiz\n");
        printf("8. Exit\n");
        printf("Enter your choice (1-8): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }

        clear_input_buffer();

switch (choice) {
        case 1:
            run_bitwise_and_quiz();
            break;
        case 2:
            run_binary_first_quiz();
            break;
        case 3:
            run_bitwise_xor_quiz();
            break;
        case 4:
            run_bitwise_or_quiz();
            break;
        case 5:
            run_bitwise_not_quiz();
            break;
        case 6:
            run_binary_decimal_conversion_quiz();
            break;
        case 7:
            run_shift_quiz();
            break;
        case 8:
            printf("Thank you for using Bitwise Tutor. Goodbye!\n");
            running = false;
            break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
