#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SYMBOLS 100
#define MAX_NAME_LEN 50

// Structure for a symbol table entry
typedef struct {
    char name[MAX_NAME_LEN];  // Identifier name
    char type[15];            // Data type: int, float, char, etc.
    char scope[10];           // Scope: global or local
    void *address;            // Memory address
    int size;                 // Size of variable in bytes
} Symbol;

// Symbol Table
Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

// List of data types with their sizes
typedef struct {
    char type[15];
    int size;
} DataTypeSize;

DataTypeSize dataTypes[] = {
    {"int", sizeof(int)},
    {"float", sizeof(float)},
    {"char", sizeof(char)},
    {"double", sizeof(double)},
    {"void", 0}  // Void has no size
};
int totalDataTypes = 5;

// Function to get the size of a data type
int getDataTypeSize(char *type) {
    int i;
    for (i = 0; i < totalDataTypes; i++) {
        if (strcmp(type, dataTypes[i].type) == 0)
            return dataTypes[i].size;
    }
    return 0;
}

// Function to check if a string is a data type
int isDataType(char *word) {
    int i;
    for ( i = 0; i < totalDataTypes; i++) {
        if (strcmp(word, dataTypes[i].type) == 0)
            return 1;
    }
    return 0;
}

// Function to check if an identifier already exists in the symbol table
int identifierExists(char *name, char *scope) {
    int i;
    for ( i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0 && strcmp(symbolTable[i].scope, scope) == 0)
            return 1;  // Already exists
    }
    return 0;
}

// Function to insert an identifier into the symbol table
void insertIdentifier(char *name, char *type, char *scope) {
    if (symbolCount >= MAX_SYMBOLS) {
        printf("Error: Symbol table is full!\n");
        return;
    }

    if (identifierExists(name, scope)) {
        return;
    }

    // Allocate memory dynamically for address
    void *memAddr = malloc(getDataTypeSize(type));

    // Store symbol details
    strcpy(symbolTable[symbolCount].name, name);
    strcpy(symbolTable[symbolCount].type, type);
    strcpy(symbolTable[symbolCount].scope, scope);
    symbolTable[symbolCount].address = memAddr;
    symbolTable[symbolCount].size = getDataTypeSize(type);
    symbolCount++;
}

// Function to display the symbol table
void displaySymbolTable() {
    printf("\n-------------------------------------------------------------");
    printf("\n| %-12s | %-10s | %-10s | %-10s | %-5s |", "Name", "Type", "Scope", "Address", "Size");
    printf("\n-------------------------------------------------------------");
    int i;
    for (i = 0; i < symbolCount; i++) {
        printf("\n| %-12s | %-10s | %-10s | %p | %-5d |",
            symbolTable[i].name, symbolTable[i].type,
            symbolTable[i].scope, symbolTable[i].address, symbolTable[i].size);
    }
    printf("\n-------------------------------------------------------------\n");
}

// Main function
int main() {
    FILE *fp;
    char buffer[50], prevWord[50] = "", ch;
    int i = 0;
    char scope[10] = "global";  // Default scope
    char currentType[15] = "";  // Store current data type

    fp = fopen("input1.txt", "r");  // Open input file
    if (fp == NULL) {
        printf("Error: Unable to open the file!\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        // Track scope changes
        if (ch == '{') {
            strcpy(scope, "local");
        } else if (ch == '}') {
            strcpy(scope, "global");
        }

        // Collect identifiers
        if (isalnum(ch) || ch == '_') {  // Allow variable names with underscore
            buffer[i++] = ch;
        } else {
            if (i > 0) {  // If buffer contains a word
                buffer[i] = '\0';  // End the string
                i = 0;

                if (isDataType(buffer)) {
                    strcpy(currentType, buffer);  // Store the current data type
                } else if (!isdigit(buffer[0]) && strlen(currentType) > 0) {
                    insertIdentifier(buffer, currentType, scope);
                    strcpy(currentType, "");  // Reset type after inserting variable
                }
            }
        }
    }

    fclose(fp);  // Close file

    // Display the symbol table
    displaySymbolTable();

    return 0;
}
