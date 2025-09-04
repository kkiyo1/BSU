#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int minElement(int* arr, int i, int &n) {
    if (i == n) {
        return arr[0];
    }
    int min = minElement(arr, i + 1, n);
    return (arr[i] < min) ? arr[i] : min;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RU");

    char line[256];
    ifstream inputFile("input.txt");

    inputFile.getline(line, sizeof(line));
    inputFile.close();

    cout << "Считанная строка: " << line << endl;

    char line_copy[256];
    strcpy_s(line_copy, line);

    int count = 0;
    char* context;
    char* token = strtok_s(line, " ", &context);
    while (token != nullptr) {
        count++;
        token = strtok_s(nullptr, " ", &context);
    }

    int* arr = new int[count];
    int i = 0;

    token = strtok_s(line_copy, " ", &context);
    while (token != nullptr) {
        arr[i] = stoi(token);
        i++;
        token = strtok_s(nullptr, " ", &context);
    }
    for (int i = 0; i < count; i++) cout << arr[i] << " ";

    ofstream outputFile("output.txt");
    outputFile << "Минимальный элемент массива: " << minElement(arr, 0, count);
    return 0;
}
