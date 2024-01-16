#include "helper.h"
#include "sequential/recursive/levenshtein_recursive.c"
#include "sequential/iterative/matrix/levenshtein_iterative.c"
#include "sequential/iterative/rows/levenshtein_iterative_optimized.c"
#include "parallel/levenshtein_parallel.c"
#include "parallel/levenshtein_parallel_2.c"

const int NUM_THREADS = 8;

int main(int argc, char **argv) {
    char a[] = {'M', 'a', 'c', 'k', 'a', '\0'};
    char b[] = {'T', 'a', 'c', 'k', 'a', 's', 't', '\0'};
    benchmark(a, b, recursive, strlen(a), strlen(b), NUM_THREADS);
    benchmark(a, b, iterative, strlen(a), strlen(b), NUM_THREADS);
    benchmark(a, b, iterative_optimized, strlen(a), strlen(b), NUM_THREADS);
    benchmark(a, b, parallel_diagonal, strlen(a), strlen(b), NUM_THREADS);
    benchmark(a, b, parallel_table, strlen(a), strlen(b), NUM_THREADS);

    return 0;
}