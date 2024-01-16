#include <stdio.h>
#include <string.h>
#include "../helper.h"

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

    #pragma omp parallel for
    for (int i = 0; i <= m; i++) {
        matrix[i][0] = i;
    }

    #pragma omp parallel for
    for (int j = 0; j <= n; j++) {
        matrix[0][j] = j;
    }

    for (int i = 1; i <= m + n; i++) {
        #pragma omp parallel for firstprivate(i)
        for (int j = i - 1; j >= 1; j--) {
            int y = i - j;
            int x = j;
            if (x <= n && y <= m) {
                int cost = (a[y - 1] == b[x - 1]) ? 0 : 1;
                matrix[x][y] = min_of_three(
                        matrix[x - 1][y] + 1, 
                        matrix[x][y - 1] + 1,
                        matrix[x - 1][y - 1] + cost
                );
            }
        }
    }

    return matrix[n][m];
}

int main() {
    char a[] = {'M', 'a', 'c', 'k', 'a', '\0'};
    char b[] = {'T', 'a', 'c', 'k', 'a', 's', 't', '\0'};
    int levenshtein_distance = calculate(a, b);
    printf("Levenshtein distance for strings %s and %s: %d\n", a, b, levenshtein_distance);
    return 0;
}