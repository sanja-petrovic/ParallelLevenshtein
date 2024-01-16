#include <stdio.h>
#include <string.h>
#include "../../../helper.h"

int calculate(char *a, char *b) {
    int m = strlen(a);
    int n = strlen(b);

    if(is_trivial(m, n)) {
        return get_trivial_result(m, n);
    }

    int *previous = create_array(n + 1);
    int *current = create_array(n + 1);

    for (int j = 0; j <= n; j++) {
        previous[j] = j;
    }


    for (int i = 1; i <= m; i++) {
        current[0] = i;
        for (int j = 1; j <= n; j++) {
            int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            current[j] = min_of_three(
                current[j - 1] + 1,
                previous[j] + 1,
                previous[j - 1] + cost
            );
        }
        for (int j = 0; j <= n; j++) {
            previous[j] = current[j];
        }
    }

    int result = current[n];
    free(current);
    free(previous);

    return result;
}

int main() {
    char a[] = {'M', 'a', 'c', 'k', 'a', '\0'};
    char b[] = {'T', 'a', 'c', 'k', 'a', 's', 't', '\0'};
    int levenshtein_distance = calculate(a, b);
    printf("Levenshtein distance for strings %s and %s: %d\n", a, b, levenshtein_distance);
    return 0;
}