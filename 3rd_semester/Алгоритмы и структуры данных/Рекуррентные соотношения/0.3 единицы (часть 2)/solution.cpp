#include <iostream>;

const long long mod = 1000000007;

int main() {
    unsigned long n, k;
    std::cin >> n >> k;

    if (k < 0 || k > n) {
        std::cout << 0;
        return 0;
    }
    if (k > n - k) {
        k = n - k;
    }
    unsigned long c = n - k;

    long long factN = 1;
    long long factK = 1;
    long long factC = 1;
    for (int i = 2; i <= n;i++) factN = (factN * i) % mod;
    for (int i = 2; i <= k;i++) factK = (factK * i) % mod;
    for (int i = 2; i <= c;i++) factC = (factC * i) % mod;

    long long znamenatel = (factK * factC) % mod;
    long long stepen = mod - 2;
    long long obr_znamenatel = 1;
    long long a = znamenatel;

    while (stepen > 0) {
        if (stepen & 1) {
            obr_znamenatel = (obr_znamenatel * a) % mod;
        }
        a = (a * a) % mod;
        stepen >>= 1;
    }

    long long result = (factN * obr_znamenatel) % mod;
    std::cout << result;

    return 0;
}