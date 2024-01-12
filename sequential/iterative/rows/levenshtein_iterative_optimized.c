#include <stdio.h>
#include <string.h>
#include "../../../helper.h"

int calculate(char *a, char *b) {
    int m = strlen(a);
    int n = strlen(b);
}

int main() {
    char a[] = {'M', 'a', 'c', 'k', 'a', '\0'};
    char b[] = {'T', 'a', 'c', 'k', 'a', 's', 't', '\0'};
    int levenshtein_distance = calculate(a, b);
    printf("Levenshtein distance for strings %s and %s: %d\n", a, b, levenshtein_distance);
    return 0;
}