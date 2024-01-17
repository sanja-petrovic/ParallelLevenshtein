#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


int min(int x, int y) {
    return (x <= y) ? x : y;
}

int max(int x, int y) {
    return (x >= y) ? x : y;
}

int min_of_three(int x, int y, int z) {
    return (x < y) ? min(x, z) : min(y, z);
}

int* create_array(int size) {
    return (int*) malloc(size * sizeof(int));
}

int** create_matrix(int m, int n) {
    int **matrix = (int**) malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        matrix[i] = create_array(n);
    }

    return matrix;
}

int** fill_initial_values(int **matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        matrix[i][0] = i;
    }

    for (int j = 0; j < n; j++) {
        matrix[0][j] = j;
    }

    return matrix;
}

int** fill_initial_values_parallel(int **matrix, int m, int n) {
    #pragma omp parallel for
    for (int i = 0; i < m; i++) {
        matrix[i][0] = i;
    }

    #pragma omp parallel for
    for (int j = 0; j < n; j++) {
        matrix[0][j] = j;
    }

    return matrix;
}

void free_matrix(int** matrix, int m) {
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int is_trivial(int m, int n) {
    return m == 0 || n == 0;
}

int get_trivial_result(int m, int n) {
    return max(m, n);
}

int get_index(char letter, char *characters) {
    int index = -1;

    for (int i = 0; i < strlen(characters); i++) {
        if (characters[i] == letter) {
        index = i;
        break;
        }
    }
    return index;
}

void benchmark(char *a, char *b, int (*f)(char *, char *, int, int, int), int m, int n, int num_threads, char *id) {
    clock_t start = clock();
    int distance = f(a, b, m, n, num_threads);
    clock_t stop = clock();
    double t = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("%s-%f:%d;", id, t, distance);
}