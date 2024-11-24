#include <stdio.h>
#include <string.h>

// Function to perform Naive String Matching
void naiveStringMatching(const char* text, const char* pattern) {
    int textLen = strlen(text);
    int patternLen = strlen(pattern);

    for (int i = 0; i <= textLen - patternLen; i++) {
        int j;
        for (j = 0; j < patternLen; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == patternLen) {
            printf("Pattern found at index %d\n", i);
        }
    }
}

int main() {
    char text[1000];
    char pattern[100];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  // Remove newline character from input

    printf("Enter the pattern to search: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';  // Remove newline character from input

    naiveStringMatching(text, pattern);

    return 0;
}
