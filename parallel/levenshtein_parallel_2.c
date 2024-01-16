
#include <omp.h>
int parallel_table(char *a, char *b, int m, int n, int num_threads) {
    if(is_trivial(m, n)) {
        return get_trivial_result(m, n);
    }
    // Део I - поставка
    // Креирање ASCII хеш табеле зa праћење карактера у стрингу а
    // Касније, ово се користи за креирање низа јединствених карактера у стрингу а
    int j = 0, last_match_index;
    int unique_count_a = 0;
    char *unique_characters_a = malloc(sizeof(int) * (unique_count_a + 1));
    int unique_iterator = 0;

    int ascii_hash_table[128] = {0};
    
    for (int i = 0; i < m; ++i) {
        ascii_hash_table[a[i]] = 1;
    }

    for (int i = 0; i < 128; ++i) {
        unique_count_a += ascii_hash_table[i];
    }

    for (int i = 0; i < 128; ++i) {
        if (ascii_hash_table[i] == 1) {
        unique_characters_a[unique_iterator++] = i;
        }
    }
    unique_characters_a[unique_iterator] = '\0';

    int **match_index_table = create_matrix(unique_count_a + 1, n + 1);
    int **matrix = create_matrix(m + 1, n + 1);

    // Део II - Креирање табеле индекса поклапања (Match Index Table)
    // узевши у обзир јединствен број карактера у првом стрингу и n карактера у другом стрингу
    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp parallel for
        for (int i = 0; i < unique_count_a; i++) {
            for (int j = 0; j < n; j++) {
                if (b[j] == unique_characters_a[i]) { 
                    // пронађено поклапање
                    match_index_table[i][j] = j;
                } else { 
                    // тренутни карактери се не поклапају
                    match_index_table[i][j] = (j == 0) ? -1 : match_index_table[i][j - 1];
                }
            }
        }
        #pragma omp barrier
        matrix = fill_initial_values_parallel(matrix, m + 1, n + 1);
        #pragma omp barrier
        // Део III - Рачунање Левенштајновог растојања користећи матрицу, слично као по Вагнер-Фишеровом алгоритму
        for (int i = 1; i <= m; i++) {
            int ind = get_index(a[i - 1], unique_characters_a); // индекс карактера а у табели јединствености
            #pragma omp parallel for
            for (j = 1; j <= n; j++) {
                int last_match_index = match_index_table[ind][j - 1] + 1; // индекс на коме се налазило последње поклапање за овај карактер
                if (j == last_match_index) { // случај 1: тренутно поклапање
                    matrix[i][j] = matrix[i - 1][j - 1];
                } else if ((last_match_index == -1) || (last_match_index == 0)) { // случај 2: поклапање још није пронађено
                    matrix[i][j] = min(
                        matrix[i - 1][j - 1] + 1, 
                        matrix[i - 1][j] + 1
                    );
                } else if (j > last_match_index) { // случај 3: поклапање је пронађено раније
                    matrix[i][j] = min_of_three(
                        matrix[i - 1][j - 1] + 1, 
                        matrix[i - 1][j] + 1,
                        matrix[i - 1][last_match_index - 1] + (j - last_match_index));
                }
            }
        }
    }

    free(unique_characters_a);
    int return_val = matrix[m][n];

    free_matrix(match_index_table, unique_count_a + 1);
    free_matrix(matrix, m + 1);
    return return_val;
}

/*int main() {
    char a[] = {'M', 'a', 'c', 'k', 'a', '\0'};
    char b[] = {'T', 'a', 'c', 'k', 'a', 's', 't', '\0'};
    benchmark(a, b, parallel_table, strlen(a), strlen(b), 4);
    return 0;
}*/