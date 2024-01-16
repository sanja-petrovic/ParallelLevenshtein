int iterative(char *a, char *b, int m, int n, int num_threads) {
    if(is_trivial(m, n)) {
        return get_trivial_result(m, n);
    }

    int **matrix = create_matrix(m + 1, n + 1);
    matrix = fill_initial_values(matrix, m + 1, n + 1);

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

    int result = matrix[m][n];
    free_matrix(matrix, m + 1);
    return result;
}


/*int main() {
    char a[] = {'M', 'a', 'c', 'k', 'a', '\0'};
    char b[] = {'T', 'a', 'c', 'k', 'a', 's', 't', '\0'};
    benchmark(a, b, iterative, strlen(a), strlen(b), 4);
    return 0;
}*/