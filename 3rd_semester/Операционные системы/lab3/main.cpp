#include "C:\Users\user\Desktop\osLabs\lab3_test\lab3_test\pch.h"
#include <iostream>
#include "header.h"
#include <Windows.h>

HANDLE startEvent;
HANDLE* continueEvents;
HANDLE* stopEvents;
HANDLE* threadStoppedEvents;
int* arr;
int n, threadCount, activeThreads;
CRITICAL_SECTION cs;

int main() {
    InitializeCriticalSection(&cs);
    std::cout << "Enter array size: ";
    std::cin >> n;
    arr = new int[n] {};

    std::cout << "Enter number of threads: ";
    std::cin >> threadCount;
    activeThreads = threadCount;

    startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    continueEvents = new HANDLE[threadCount];
    stopEvents = new HANDLE[threadCount];
    threadStoppedEvents = new HANDLE[threadCount];

    for (int i = 0; i < threadCount; i++) {
        continueEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        stopEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        threadStoppedEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
    }

    HANDLE* hThreads = new HANDLE[threadCount];

    for (int i = 0; i < threadCount; i++) {
        int* threadId = new int(i);
        hThreads[i] = CreateThread(NULL, 0, marker, threadId, 0, NULL);
        if (hThreads[i] == NULL) {
            std::cout << "Error creating thread " << i << std::endl;
            return -1;
        }
    }
    SetEvent(startEvent);

    while (activeThreads > 0) {
        WaitForMultipleObjects(threadCount, threadStoppedEvents, TRUE, INFINITE);
        std::cout << "Array: ";
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }

        if (activeThreads == 0) break;
        int index;
        std::cout << "Enter thread number to finish (0-" << threadCount - 1 << "): ";
        std::cin >> index;

        if (index < 0 || index >= threadCount || hThreads[index] == NULL) {
            std::cout << "Invalid thread number!" << std::endl;
            continue;
        }

        SetEvent(stopEvents[index]);
        WaitForSingleObject(hThreads[index], INFINITE);

        EnterCriticalSection(&cs);
        CloseHandle(hThreads[index]);
        hThreads[index] = NULL;
        activeThreads--;
        LeaveCriticalSection(&cs);
        std::cout << "Array after stopping thread " << index << ": ";
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;

        if (activeThreads == 0) break;

        for (int i = 0; i < threadCount; i++) {
            if (hThreads[i] != NULL) {
                ResetEvent(threadStoppedEvents[i]);
            }
        }

        std::cout << "Resuming remaining threads..." << std::endl;
        for (int i = 0; i < threadCount; i++) {
            if (hThreads[i] != NULL) {
                SetEvent(continueEvents[i]);
            }
        }
    }

    std::cout << "All threads finished. Cleaning up..." << std::endl;

    for (int i = 0; i < threadCount; i++) {
        CloseHandle(continueEvents[i]);
        CloseHandle(stopEvents[i]);
        CloseHandle(threadStoppedEvents[i]);
    }
    CloseHandle(startEvent);
    DeleteCriticalSection(&cs);

    delete[] hThreads;
    delete[] threadStoppedEvents;
    delete[] stopEvents;
    delete[] continueEvents;
    delete[] arr;

    std::cout << "Program finished successfully!" << std::endl;
    return 0;
}   