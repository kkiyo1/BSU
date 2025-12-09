#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <climits>

int calculate(std::vector<std::pair<int, int>>& arr) {
    int n = arr.size();

    int** dp = new int* [n];
    for (int i = 0; i < n; i++) {
        dp[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dp[i][j] = 0;
            }
        }
    }

    for (int l = 2; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int operations = dp[i][k] + dp[k + 1][j] + arr[i].first * arr[k].second * arr[j].second;
                if (operations < dp[i][j]) {
                    dp[i][j] = operations;
                }
            }
        }
    }

    int result = dp[0][n - 1];

    for (int i = 0; i < n; i++) {
        delete[] dp[i];
    }
    delete[] dp;

    return result;
}

int main() {
    int n;
    std::vector<std::pair<int, int>> arr;
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    inputFile >> n;
    for (int i = 0; i < n; i++) {
        int rows, columns;
        inputFile >> rows >> columns;
        arr.push_back(std::make_pair(rows, columns));
    }
    inputFile.close();
    outputFile << calculate(arr);
    outputFile.close();
    return 0;
}