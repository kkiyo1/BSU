#include <iostream>
#include <time.h>
#include <iomanip>
#include <cstdio>
#include <cstdlib> 

using namespace std;

void generateMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) matrix[i][j] = rand() % 10 + 1;
    }
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%5d", matrix[i][j]);
        printf("\n\n");
    }
}

void switchElements(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) swap(matrix[i][j], matrix[j][i]);
    }
}

void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RU");
    srand(time(0));

    if (argc != 2) {
        cout << "Использование: " << argv[0] << " <размер матрицы>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        cout << "Размер матрицы должен быть положительным числом." << endl;
        return 1;
    }

    int** matrix = new int* [n];
    generateMatrix(matrix, n);
    cout << "Изначальная матрица: " << endl;
    printMatrix(matrix, n);
    switchElements(matrix, n);
    cout << "Отраженная матрица: " << endl;
    printMatrix(matrix, n);
    deleteMatrix(matrix, n);
    return 0;
}
