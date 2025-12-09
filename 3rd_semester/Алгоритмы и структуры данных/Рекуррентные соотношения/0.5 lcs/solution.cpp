#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> indexesA;
std::vector<int> indexesB;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int calculate(int* a, int* b, int n) {
    int** dp = new int* [n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = new int[n + 1];
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i] == b[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            }
            else {
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }

    int i = n, j = n;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            indexesA.push_back(i - 1);
            indexesB.push_back(j - 1);
            i--;
            j--;
        }
        else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }
    std::reverse(indexesA.begin(), indexesA.end());
    std::reverse(indexesB.begin(), indexesB.end());

    int result = dp[n][n];

    for (int i = 0; i <= n; i++) {
        delete[] dp[i];
    }
    delete[] dp;
    return result;
}

int main() {
    int n;
    std::cin >> n;
    int* a = new int[n];
    int* b = new int[n];
    for (int i = 0; i < n; i++) std::cin >> a[i];
    for (int i = 0; i < n; i++) std::cin >> b[i];

    std::cout << calculate(a, b, n) << '\n';
    for (int i = 0; i < indexesA.size(); i++) std::cout << indexesA[i] << " ";
    std::cout << '\n';
    for (int i = 0; i < indexesB.size(); i++) std::cout << indexesB[i] << " ";
    delete[] b;
    delete[] a;
    return 0;
}