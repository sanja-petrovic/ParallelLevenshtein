#include "../../../helper.h"

int calculate(char *a, char *b) {
    int m = strlen(a);
    int n = strlen(b);

    int matrix[m + 1][n + 1];
    if (m == 0) {
        return n;
    }
    if (n == 0) {
        return m;
    }

    for (int i = 0; i <= m; i++) {
        matrix[i][0] = i;
    }

    for (int j = 0; j <= n; j++) {
        matrix[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            matrix[i][j] = min_of_three(
                matrix[i - 1][j] + 1,
                matrix[i][j - 1] + 1,
                matrix[i - 1][j - 1] + cost
            );
        }
    }

    return matrix[m][n];
}

int main() {
    char a[] = {'M', 'a', 'c', 'k', 'a', '\0'};
    char b[] = {'T', 'a', 'c', 'k', 'a', 's', 't', '\0'};
    int levenshtein_distance = calculate(a, b);
    printf("Levenshtein distance for strings %s and %s: %d\n", a, b, levenshtein_distance);
    return 0;
}