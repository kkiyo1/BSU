#include <Windows.h>
#include <iostream>
#include "header.h"
#include <thread>

int main() {
    std::cout << "===================================================================================='\n'";
    std::cout << "Enter array size: ";
    std::cin >> n;
    int* arr = new int[n];

    std::cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::thread minMaxThread(min_max_func, arr);
    std::thread averageThread(average_func, arr);
    minMaxThread.join();
    averageThread.join();

    for (int i = 0; i < indexes.size(); i++) arr[indexes[i]] = average;

    std::cout << "Result array: ";
    for (int i = 0; i < n; i++) std::cout << arr[i] << " ";
    std::cout << "\n====================================================================================\n";

    delete[] arr;
    return 0;
}