#include "helper.h"
#include "sequential/recursive/levenshtein_recursive.c"
#include "sequential/iterative/matrix/levenshtein_iterative.c"
#include "sequential/iterative/rows/levenshtein_iterative_optimized.c"
#include "parallel/levenshtein_parallel.c"
#include "parallel/levenshtein_parallel_2.c"

int test(char *a, char *b, int m, int n, int num_threads) {
    //benchmark(a, b, recursive, m, n, num_threads, "r");
    benchmark(a, b, iterative, m, n, num_threads, "i");
    benchmark(a, b, iterative_optimized, m, n, num_threads, "i_o");
    benchmark(a, b, parallel_diagonal, m, n, num_threads, "p_d");
    benchmark(a, b, parallel_table, m, n, num_threads, "p_t");
}

int main(int argc, char **argv) {
    FILE *in = fopen(argv[3], "r");
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int num_threads = atoi(argv[4]);
    char a[m];
    char b[n];
    fscanf(in, "%s %s", a, b);
    fclose(in);
    test(a, b, m, n, num_threads);

    return 0;
}