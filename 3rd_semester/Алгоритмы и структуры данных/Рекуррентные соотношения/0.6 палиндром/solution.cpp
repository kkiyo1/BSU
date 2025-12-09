#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

std::string palyndrome = "";

int max(int a, int b) {
    return (a > b) ? a : b;
}

int calculate(std::string& s1, std::string& s2, int n) {
    int** dp = new int* [n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = new int[n + 1];
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s1[i] == s2[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            }
            else {
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }

    int i = n, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            palyndrome += s1[i - 1];
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

    int result = dp[n][n];
    for (int i = 0; i <= n; i++) {
        delete[] dp[i];
    }
    delete[] dp;
    return result;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    std::string s1;
    inputFile >> s1;
    std::string s2(s1.rbegin(), s1.rend());
    int result = calculate(s1, s2, s1.size());
    outputFile << result << '\n' << palyndrome;
    return 0;
}