
int parallel_diagonal(char *a, char *b, int m, int n, int num_threads) {
    if(is_trivial(m, n)) {
        return get_trivial_result(m, n);
    }
    
    int **matrix = create_matrix(m + 1, n + 1);
    omp_set_num_threads(num_threads);

    #pragma omp parallel 
    {
        #pragma omp for nowait
        for (int i = 0; i < m; i++) {
            matrix[i][0] = i;
        }

        #pragma omp for
        for (int j = 0; j < n; j++) {
            matrix[0][j] = j;
        }
        for (int i = 1; i <= m + n; i++) {
            #pragma omp for schedule(static, 24)
            for (int j = i - 1; j >= 1; j--) {
                int y = i - j;
                int x = j;
                if (x <= m && y <= n) {
                    int cost = (a[y - 1] == b[x - 1]) ? 0 : 1;
                    matrix[x][y] = min_of_three(
                            matrix[x - 1][y] + 1, 
                            matrix[x][y - 1] + 1,
                            matrix[x - 1][y - 1] + cost
                    );
                }
            }
        }
    }
    
    int res = matrix[m][n];
    free_matrix(matrix, m + 1);

    return res;
}

/*int main() {
    char a[] = {'M', 'a', 'c', 'k', 'a', '\0'};
    char b[] = {'T', 'a', 'c', 'k', 'a', 's', 't', '\0'};
    benchmark(a, b, parallel_diagonal, strlen(a), strlen(b), 4);
    return 0;
}*/