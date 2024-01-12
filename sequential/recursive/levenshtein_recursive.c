#include <stdio.h>
#include <string.h>

int min(int x, int y) {
    return (x <= y) ? x : y;
}

int min_of_three(int x, int y, int z) {
    return (x < y) ? min(x, z) : min(y, z);
}

int calculate(char *a, char *b, size_t i, size_t j) {
    if (i == 0) {
        return j;
    }
    if (j == 0) {
        return i;
    }
    int cost = (a[i-1] == b[j-1]) ? 0 : 1;
    
    int res = min_of_three(
        calculate(a, b, i - 1, j) + 1,
        calculate(a, b, i, j - 1) + 1,
        calculate(a, b, i - 1, j - 1) + cost
    );

    return res;
}

int main() {
    char a[] = {'M', 'a', 'c', 'k', 'a', '\0'};
    char b[] = {'T', 'a', 'c', 'k', 'a', 's', 't', '\0'};
    int levenshtein_distance = calculate(a, b, strlen(a), strlen(b));
    printf("Levenshtein distance for strings %s and %s: %d\n", a, b, levenshtein_distance);
    return 0;
}