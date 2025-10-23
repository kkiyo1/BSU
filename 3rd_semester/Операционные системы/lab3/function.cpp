#include "C:\Users\user\Desktop\osLabs\lab3_test\lab3_test\pch.h"
#include <iostream>
#include <Windows.h>
#include "header.h"

DWORD marker(LPVOID param) {
    WaitForSingleObject(startEvent, INFINITE);
    int threadId = *(int*)param;
    delete (int*)param;
    srand(threadId);

    int markedCount = 0;
    bool working = true;

    while (working) {
        int num = rand() % n;
        EnterCriticalSection(&cs);
        if (arr[num] == 0) {
            Sleep(5);
            arr[num] = threadId + 1;
            markedCount++;
            Sleep(5);
            LeaveCriticalSection(&cs);
        }
        else {
            LeaveCriticalSection(&cs);
            std::cout << "Thread " << threadId << " cannot mark element " << num << " (marked " << markedCount << " elements)" << std::endl;
            SetEvent(threadStoppedEvents[threadId]);
            HANDLE events[2] = { continueEvents[threadId], stopEvents[threadId] };
            DWORD result = WaitForMultipleObjects(2, events, FALSE, INFINITE);

            if (result == WAIT_OBJECT_0 + 1) {
                EnterCriticalSection(&cs);
                for (int i = 0; i < n; i++) {
                    if (arr[i] == threadId + 1) {
                        arr[i] = 0;
                    }
                }
                LeaveCriticalSection(&cs);
                working = false;
            }
            else {
                ResetEvent(continueEvents[threadId]);
            }
        }
    }

    std::cout << "Thread " << threadId << " finished work" << std::endl;
    return 0;
}