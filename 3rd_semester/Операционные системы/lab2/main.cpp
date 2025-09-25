#include <Windows.h>
#include <iostream>
#include "header.h"

DWORD main_exitCode;

int main() {
    std::cout << "====================================================================================" << '\n';
    std::cout << "Enter array size: ";
    std::cin >> n;
    DWORD* arr = new DWORD[n];

    std::cout << "Enter " << n << " elements: ";
    for (DWORD i = 0; i < n; i++) {
        std::cin >> arr[i];
    }



    DWORD IDThread1, IDThread2;
    HANDLE hMinMaxThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)min_max_func,
        arr,
        0,
        &IDThread1
    );

    if (NULL == hMinMaxThread) {
        std::cout << "Thread creating error";
        delete[] arr;
        ExitThread(main_exitCode);
    }

    HANDLE hAverageThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)average_func,
        arr,
        0,
        &IDThread2
    );

    if (NULL == hAverageThread) {
        std::cout << "Thread creating error";
        delete[] arr;
        ExitThread(main_exitCode);
    }

    WaitForSingleObject(hMinMaxThread, INFINITE);
    WaitForSingleObject(hAverageThread, INFINITE);
    
    for (DWORD i = 0; i < indexes.size(); i++) arr[indexes[i]] = average;

    std::cout << "Result array: ";
    for (DWORD i = 0; i < n; i++) std::cout << arr[i] << " ";
    std::cout << "\n====================================================================================\n";

    delete[] arr;
    CloseHandle(hMinMaxThread);
    CloseHandle(hAverageThread);
    ExitThread(main_exitCode);
}