#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function to check if a string is an identifier (NFA simulation)
int is_identifier(const char *str) {
    int state = 0; // Start state
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];

        // State transitions based on the current state and character
        switch (state) {
            case 0:
                if (isalpha(ch)) state = 1;  // Start with a letter
                else return 0;  // Invalid start
                break;
            case 1:
                if (isalnum(ch)) state = 1;  // Stay in state 1 (can have alphanumeric characters)
                else return 0;  // Invalid character
                break;
        }
    }
    return (state == 1);  // Accepts if we end in state 1
}

// Function to check if a string is a constant (integer or float) using NFA-like logic
int is_constant(const char *str) {
    int state = 0; // Start state
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];

        // State transitions based on the current state and character
        switch (state) {
            case 0:
                if (isdigit(ch)) state = 1;  // Start with a digit
                else return 0;  // Invalid start
                break;
            case 1:
                if (isdigit(ch)) state = 1;  // Continue with digits
                else if (ch == '.') state = 2; // Decimal point for float
                else return 0;  // Invalid character
                break;
            case 2:
                if (isdigit(ch)) state = 3;  // Decimal part
                else return 0;  // Invalid character after decimal
                break;
            case 3:
                if (isdigit(ch)) state = 3;  // Continue with digits after decimal
                else return 0;  // Invalid character
                break;
        }
    }
    return (state == 1 || state == 3); // Accepts if we end in state 1 (integer) or state 3 (float)
}

// Function to check if a string is an operator using NFA-like transitions
int is_operator(const char *str) {
    // List of possible operators
    char *operators[] = {"+", "-", "*", "/", "=", "==", "<", ">", "<=", ">=", "!="};
    int num_operators = sizeof(operators) / sizeof(operators[0]);

    // Try matching each operator in the list (simulate non-deterministic transitions)
    for (int i = 0; i < num_operators; i++) {
        if (strcmp(str, operators[i]) == 0) {
            return 1;  // Match found
        }
    }
    return 0;  // No match
}

int main() {
    char *test_strings[] = {"x123", "variable", "3.14", "42", "<=", "==", "!=", "+", "9x", "hello123"};
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; i++) {
        char *str = test_strings[i];

        if (is_identifier(str))
            printf("'%s' is an Identifier\n", str);
        else if (is_constant(str))
            printf("'%s' is a Constant\n", str);
        else if (is_operator(str))
            printf("'%s' is an Operator\n", str);
        else
            printf("'%s' is Unrecognized\n", str);
    }

    return 0;
}
