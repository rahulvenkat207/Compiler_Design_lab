#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// List of keywords
char *keywords[] = {"int", "float", "char", "double", "if", "else", "while", "for", "return", "void"};
int keywordCount = 10;

// Check if a string is a keyword
int isKeyword(char *str) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check if a character is an operator
int isOperator(char ch) {
    char operators[] = "+-*/%=<>&|!";
    for (int i = 0; operators[i] != '\0'; i++) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}

// Check if a character is a special symbol
int isSpecialSymbol(char ch) {
    char symbols[] = "(){}[];,"; // Special symbols in C
    for (int i = 0; symbols[i] != '\0'; i++) {
        if (ch == symbols[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *file = fopen("source_code.txt", "r");
    if (!file) {
        printf("Error: Could not open file\n");
        return 1;
    }

    char ch, buffer[100];
    int index = 0;

    // Token counters
    int keywordCount = 0;
    int identifierCount = 0;
    int numberCount = 0;
    int operatorCount = 0;
    int specialSymbolCount = 0;

    int tokenCount = 0; // Total token counter

    while ((ch = fgetc(file)) != EOF) {
        // Handle identifiers, keywords, or numbers
        if (isalnum(ch) || ch == '.') {
            buffer[index++] = ch;
        } else {
            if (index > 0) {
                buffer[index] = '\0';
                // Token identified: Check its type
                if (isKeyword(buffer)) {
                    printf("Keyword: %s\n", buffer);
                    keywordCount++; // Increment keyword counter
                } else if (isdigit(buffer[0])) {
                    printf("Number: %s\n", buffer);
                    numberCount++; // Increment number counter
                } else {
                    printf("Identifier: %s\n", buffer);
                    identifierCount++; // Increment identifier counter
                }
                tokenCount++; // Increment total token count
                index = 0;
            }

            // Handle operators
            if (isOperator(ch)) {
                printf("Operator: %c\n", ch);
                operatorCount++; // Increment operator counter
                tokenCount++; // Increment total token count
            }

            // Handle special symbols
            if (isSpecialSymbol(ch)) {
                printf("Special Symbol: %c\n", ch);
                specialSymbolCount++; // Increment special symbol counter
                tokenCount++; // Increment total token count
            }
        }
    }

    // Check if there was a trailing token
    if (index > 0) {
        buffer[index] = '\0';
        if (isKeyword(buffer)) {
            printf("Keyword: %s\n", buffer);
            keywordCount++; // Increment keyword counter
        } else
         if (isdigit(buffer[0])) {
            printf("Number: %s\n", buffer);
            numberCount++; // Increment number counter
        } else {
            printf("Identifier: %s\n", buffer);
            identifierCount++; // Increment identifier counter
        }
        tokenCount++; // Increment total token count
    }

    // Output the total number of tokens
    printf("\nTotal number of tokens: %d\n", tokenCount);

    // Output the counts for each token type
    printf("\nToken Counts:\n");
    printf("Keywords: %d\n", keywordCount);
    printf("Identifiers: %d\n", identifierCount);
    printf("Numbers: %d\n", numberCount);
    printf("Operators: %d\n", operatorCount);
    printf("Special Symbols: %d\n", specialSymbolCount);

    fclose(file);
    return 0;
}
