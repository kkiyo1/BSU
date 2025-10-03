#include "header.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <thread>

int n = 0;
std::vector<int> indexes;
int average = 0;

void min_max_func(int* arr) {

    if (nullptr == arr || 0 == n) {
        return;
    }

    int min_val = arr[0];
    int max_val = arr[0];
    int min_index = 0, max_index = 0;
    indexes.clear();
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            min_index = i;
        }
        Sleep(7);
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_index = i;
        }
        Sleep(7);
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] == min_val || arr[i] == max_val) indexes.push_back(i);
    }

    std::cout << "Min value: " << min_val << '\n' << "Max value: " << max_val << '\n';
    return;
}

void average_func(int* arr) {
    if (nullptr == arr || 0 == n) {
        average = 0;
        return;
    }

    int summ = 0;
    for (int i = 0; i < n; i++) {
        summ += arr[i];
        Sleep(12);
    }
    average = summ / n;
    std::cout << "Average value: " << average << '\n';
    return;
}