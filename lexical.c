#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKENS 100
#define MAX_LENGTH 50

// Storage for different token types
char keywords[MAX_TOKENS][MAX_LENGTH];
char identifiers[MAX_TOKENS][MAX_LENGTH];
char mathOperators[MAX_TOKENS];
char logicalOperators[MAX_TOKENS];
char numericValues[MAX_TOKENS][MAX_LENGTH];
char others[MAX_TOKENS];

int keywordCount = 0, identifierCount = 0, mathOpCount = 0;
int logicalOpCount = 0, numericCount = 0, othersCount = 0;

const char *keywordList[] = {"int", "float", "return", "if", "else", "while", "for", "char"};
const int keywordTotal = 8;

// Utility Functions
int isKeyword(const char *word) {
    for (int i = 0; i < keywordTotal; i++) {
        if (strcmp(word, keywordList[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isDuplicate(char array[MAX_TOKENS][MAX_LENGTH], int count, const char *value) {
    for (int i = 0; i < count; i++) {
        if (strcmp(array[i], value) == 0) {
            return 1;
        }
    }
    return 0;
}

void addUnique(char array[MAX_TOKENS][MAX_LENGTH], int *count, const char *value) {
    if (!isDuplicate(array, *count, value)) {
        strcpy(array[(*count)++], value);
    }
}

void addUniqueChar(char array[MAX_TOKENS], int *count, char value) {
    for (int i = 0; i < *count; i++) {
        if (array[i] == value) {
            return;
        }
    }
    array[(*count)++] = value;
}

// Lexical Analyzer Logic
void lexicalAnalyzer(const char *input) {
    char buffer[MAX_LENGTH];
    int index = 0;
    char ch;

    for (int i = 0; input[i] != '\0'; i++) {
        ch = input[i];

        if (isalnum(ch) || ch == '.') {  // Handling identifiers, keywords, numbers
            buffer[index++] = ch;
        } else {
            if (index > 0) {
                buffer[index] = '\0';
                index = 0;

                if (isKeyword(buffer)) {
                    addUnique(keywords, &keywordCount, buffer);
                } else if (isdigit(buffer[0])) {
                    addUnique(numericValues, &numericCount, buffer);
                } else {
                    addUnique(identifiers, &identifierCount, buffer);
                }
            }

            // Handle math and logical operators
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=') {
                addUniqueChar(mathOperators, &mathOpCount, ch);
            } else if (ch == '>' || ch == '<' || ch == '!' || ch == '&' || ch == '|') {
                addUniqueChar(logicalOperators, &logicalOpCount, ch);
            } else if (!isspace(ch) && ch != ';' && ch != ',') {
                addUniqueChar(others, &othersCount, ch);
            }
        }
    }
}

// Print Token Categories
void printTokens() {
    printf("Keywords: ");
    for (int i = 0; i < keywordCount; i++) {
        printf("%s", keywords[i]);
        if (i < keywordCount - 1) printf(", ");
    }
    printf("\nIdentifiers: ");
    for (int i = 0; i < identifierCount; i++) {
        printf("%s", identifiers[i]);
        if (i < identifierCount - 1) printf(", ");
    }
    printf("\nMath Operators: ");
    for (int i = 0; i < mathOpCount; i++) {
        printf("%c", mathOperators[i]);
        if (i < mathOpCount - 1) printf(", ");
    }
    printf("\nLogical Operators: ");
    for (int i = 0; i < logicalOpCount; i++) {
        printf("%c", logicalOperators[i]);
        if (i < logicalOpCount - 1) printf(", ");
    }
    printf("\nNumerical Values: ");
    for (int i = 0; i < numericCount; i++) {
        printf("%s", numericValues[i]);
        if (i < numericCount - 1) printf(", ");
    }
    printf("\nOthers: ");
    for (int i = 0; i < othersCount; i++) {
        printf("%c", others[i]);
        if (i < othersCount - 1) printf(", ");
    }
    printf("\n");
}

int main() {
    char input[MAX_TOKENS * MAX_LENGTH];
    printf("Enter the input: ");
    fgets(input, sizeof(input), stdin);

    lexicalAnalyzer(input);
    printTokens();
    return 0;
}
