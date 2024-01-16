#include "../../helper.h"


int calculate(char *a, char *b, size_t m, size_t n) {
    if(is_trivial(m, n)) {
        return get_trivial_result(m, n);
    }

    int cost = (a[m-1] == b[n-1]) ? 0 : 1;
    
    int res = min_of_three(
        calculate(a, b, m - 1, n) + 1,
        calculate(a, b, m, n - 1) + 1,
        calculate(a, b, m - 1, n - 1) + cost
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