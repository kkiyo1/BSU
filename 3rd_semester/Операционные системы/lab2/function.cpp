#include "header.h"
#include <Windows.h>
#include <iostream>
#include <vector>

DWORD n;
std::vector<DWORD> indexes;
DWORD average;

DWORD min_max_exitCode, average_exitCode;

void min_max_func(LPVOID lpParam) {
    DWORD* arr = (DWORD*)lpParam;

    if (nullptr == arr || 0 == n) {
        ExitThread(min_max_exitCode);
    }

    DWORD min_val = arr[0];
    DWORD max_val = arr[0];
    DWORD min_index = 0, max_index = 0;
    indexes.clear();
    for (DWORD i = 0; i < n; i++) {
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
    for (DWORD i = 0; i < n; i++) {
        if (arr[i] == min_val || arr[i] == max_val) indexes.push_back(i);
    }

    std::cout << "Min value: " << min_val << '\n' << "Max value: " << max_val << '\n';
    ExitThread(min_max_exitCode);
}

void average_func(LPVOID lpParam) {
    DWORD* arr = (DWORD*)lpParam;

    if (nullptr == arr || 0 == n) {
        ExitThread(average_exitCode);
    }

    DWORD summ = 0;
    for (DWORD i = 0; i < n; i++) {
        summ += arr[i];
        Sleep(12);
    }
    average = summ / n;
    std::cout << "Average value: " << average << '\n';
    ExitThread(average_exitCode);
}