#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int calculate(long long* arr, int n) {
    if (n == 0) return 0;

    std::vector<long long> tail;

    for (int i = 0; i < n; i++) {
        auto it = std::lower_bound(tail.begin(), tail.end(), arr[i]);
        if (it == tail.end()) tail.push_back(arr[i]);
        else *it = arr[i];
    }

    return tail.size();
}

int main() {
    int n;
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    inputFile >> n;
    long long* arr = new long long[n];
    for (int i = 0; i < n; i++) inputFile >> arr[i];
    int result = calculate(arr, n);
    outputFile << result;
    delete[] arr;
    return 0;
}