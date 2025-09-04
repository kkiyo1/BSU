#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

bool isHexadecimal(const char* s) {
    if (s == nullptr || *s == '\0') return false;
    for (const char* p = s; *p; ++p) {
        if (!isxdigit(*p)) return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "RU");
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cout << "Ошибка открытия файла input.txt" << endl;
        return 1;
    }

    string first_line;
    getline(inputFile, first_line);

    char dividers[256];
    cout << "Введите разделители: ";
    cin.getline(dividers, sizeof(dividers));

    int hexNumbers[100];
    int count = 0;

    char* token = strtok(const_cast<char*>(first_line.c_str()), dividers);

    while (token != NULL) {
        if (isHexadecimal(token)) {
            hexNumbers[count] = strtol(token, nullptr, 16);
            count++;
        }
        token = strtok(NULL, dividers);
    }

    ofstream resultFile("result.txt");
    if (count > 0) {
        shellSort(hexNumbers, count);
        resultFile << "Отсортированные шестнадцатеричные числа: ";
        for (int i = 0; i < count; i++) {
            resultFile << hexNumbers[i] << " ";
        }
        resultFile << endl;
    }
    else {
        resultFile << "Не найдено шестнадцатеричных чисел." << endl;
    }

    string str;
    for (int i = 0; i < count; i++) str += " " + to_string(hexNumbers[i]);
    srand(static_cast<unsigned int>(time(0)));
    int random_number = rand() % 100 + 1;
    cout << "Случайное число: " << random_number;
    str += " " + to_string(random_number);

    token = strtok(const_cast<char*>(first_line.c_str()), dividers);
    if (token != NULL && isHexadecimal(token)) {
        str.erase(0, strlen(token) + 1);
    }

    resultFile << "Результирующая строка: " << str << endl;
    resultFile.close();

    cout << '\n' << "Результат записан в файле result.txt";
    return 0;
}