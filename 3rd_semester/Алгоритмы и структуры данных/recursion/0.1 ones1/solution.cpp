#include <iostream>;

const int mod = 1000000007;
long long check[1001][1001];

unsigned long long count(unsigned short n, unsigned short k, unsigned short c) {
    if (0 == k || k == n || 1 == n) return 1;
    if (1 == k) return n;

    if (check[n][k] != -1) return check[n][k];

    long long result = (count(n - 1, k - 1, c) + count(n - 1, k, c)) % mod;
    check[n][k] = result;
    return result;
}

int main() {
    unsigned short n, k;
    std::cin >> n >> k;
    unsigned short c = n - k;
    for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 1001; j++)
            check[i][j] = -1;
    }
    std::cout << count(n, k, c);
    return 0;
}