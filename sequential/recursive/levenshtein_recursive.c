
int recursive(char *a, char *b, int m, int n, int num_threads) {
    if(is_trivial(m, n)) {
        return get_trivial_result(m, n);
    }

    int cost = (a[m-1] == b[n-1]) ? 0 : 1;
    
    int res = min_of_three(
        recursive(a, b, m - 1, n, num_threads) + 1,
        recursive(a, b, m, n - 1, num_threads) + 1,
        recursive(a, b, m - 1, n - 1, num_threads) + cost
    );

    return res;
}

/*int main() {
    char a[] = {'M', 'a', 'c', 'k', 'a', '\0'};
    char b[] = {'T', 'a', 'c', 'k', 'a', 's', 't', '\0'};
    benchmark(a, b, recursive, strlen(a), strlen(b), 4);
    return 0;
}*/