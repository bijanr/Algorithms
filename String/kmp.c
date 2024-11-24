#include <stdio.h>
#include <string.h>

// Function to build the partial match table (also known as LPS array)
void buildLPSArray(const char* pattern, int* lps) {
    int len = strlen(pattern);
    int length = 0; // length of the previous longest prefix suffix
    int i = 1;

    lps[0] = 0; // LPS[0] is always 0

    while (i < len) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to perform KMP String Matching
void KMPStringMatching(const char* text, const char* pattern) {
    int textLen = strlen(text);
    int patternLen = strlen(pattern);
    int lps[patternLen];

    // Build the LPS array
    buildLPSArray(pattern, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < textLen) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == patternLen) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < textLen && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
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

    KMPStringMatching(text, pattern);

    return 0;
}
